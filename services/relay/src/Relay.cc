#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <thread>
#include "toad/services/relay/Logger.hh"
#include <iostream>
#include <thread>
#include <vector>
#include <zmq.hpp>
#include <mutex>
#include <atomic>

std::atomic_int id{0};

class Worker {
public:
int id_;
    Worker(zmq::context_t& context)
        : workerSocket_(context, ZMQ_DEALER)
    {
        id_ = id++;
    }

    void work() {
        workerSocket_.connect("inproc://backend");

        while (true) {
            std::cout<<"worker id "<<id_;

            std::cout<<"na samym poczatku\n";

            zmq::message_t identity;
            zmq::message_t request;

            workerSocket_.recv(&identity);
            workerSocket_.recv(&request);
            std::cout<<"---------------\n";
            std::string id = "identity: " + std::string(static_cast<char*>(identity.data()), identity.size());
            std::string response = "request: " + std::string(static_cast<char*>(request.data()), request.size());
            std::cout<< id<<" "<<response<<std::endl;
            // Przetwarzanie żądania
            std::cout<<"czekanko\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            // Odpowiedź na żądanie
            zmq::message_t replyIdentity(identity.data(), identity.size());
            zmq::message_t replyResponse(response.size());
            memcpy(replyResponse.data(), response.data(), response.size());

            workerSocket_.send(replyIdentity, ZMQ_SNDMORE);
            workerSocket_.send(replyResponse);
            std::cout<<"na samym koncu\n";

        }
    }

private:
    zmq::socket_t workerSocket_;
};

class Server {
public:
    Server()
        : context_(1),
          frontendSocket_(context_, ZMQ_ROUTER),
          backendSocket_(context_, ZMQ_DEALER)
    {}

    void run() {
        frontendSocket_.bind("tcp://*:5570");
        backendSocket_.bind("inproc://backend");

        std::vector<std::thread> workerThreads;
        for (int i = 0; i < kNumWorkers; ++i) {
            workerThreads.emplace_back([this]() { workerTask(); });
        }

        zmq::proxy(static_cast<void*>(frontendSocket_), static_cast<void*>(backendSocket_), nullptr);

        for (auto& thread : workerThreads) {
            thread.join();
        }
    }

private:
    static constexpr int kNumWorkers = 5;

    zmq::context_t context_;
    zmq::socket_t frontendSocket_;
    zmq::socket_t backendSocket_;

    void workerTask() {
        Worker worker(context_);
        worker.work();
    }
};
using boost::asio::ip::tcp;

std::string longFOO(int t)
{
            std::this_thread::sleep_for(std::chrono::milliseconds(t));
    return "udalo sie";
}

class TCPServer {
public:
    TCPServer(boost::asio::io_context& io_context, unsigned short port)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
    {
        startAccept();
    }

private:
    void startAccept() {
        auto newConnection = std::make_shared<tcp::socket>(acceptor_.get_executor());

        acceptor_.async_accept(*newConnection,
            [this, newConnection](const boost::system::error_code& error) {
                if (!error) {
                    handleClient(std::move(newConnection));
                }

                startAccept();
            });
    }

    void handleClient(std::shared_ptr<tcp::socket> socket)
    {
        INFO_LOG("New connection");

        socket->async_read_some(boost::asio::buffer(buffer_),
            [this, socket](const boost::system::error_code& error, std::size_t bytes_transferred) {
                if (!error) {
                    handleHandshake(socket, bytes_transferred);
                } else {
                    handleDisconnect(socket);
                }
            });
    }

    void handleHandshake(std::shared_ptr<tcp::socket> socket, std::size_t length) {
        std::string message(buffer_.data(), length);
        DEBUG_LOG("Handshake: {}", message);

        socket->async_read_some(boost::asio::buffer(buffer_),
            [this, socket](const boost::system::error_code& error, std::size_t bytes_transferred)
            {
                if (!error)
                {
                    handleReceivedData(socket, bytes_transferred);
                }
                else
                {
                    WARN_LOG("Error during handshake: {}", error.message());
                    handleDisconnect(socket);
                }
            });
    }

    void handleReceivedData(std::shared_ptr<tcp::socket> socket, std::size_t length) {
        std::string message(buffer_.data(), length);
        DEBUG_LOG("Message received: {}", message);

        std::thread th([this, socket, message]() {
            auto r = std::string();
            try
            {
                r = longFOO(std::stoi(message));
            }
            catch(const std::exception& e)
            {
                r= message;
            }
            DEBUG_LOG("Message send: {}", r);
            
            boost::asio::post(socket->get_executor(),
                [this, socket, r]() {
                    socket->async_write_some(boost::asio::buffer(r),
                        [this, socket](const boost::system::error_code& error, std::size_t bytes_transferred) {
                            if (!error) {
                            } else {
                                handleDisconnect(socket);
                            }
                        });
                });
        });
        th.detach();

        socket->async_read_some(boost::asio::buffer(buffer_),
            [this, socket](const boost::system::error_code& error, std::size_t bytes_transferred)
            {
                if (!error)
                {
                    handleReceivedData(socket, bytes_transferred);
                }
                else
                {
                    WARN_LOG("Error during receive data: {}", error.message());
                    handleDisconnect(socket);
                }
            });
    }

    void handleDisconnect(std::shared_ptr<tcp::socket> socket)
    {
        INFO_LOG("The client was disconnected.");
    }

    tcp::acceptor acceptor_;
    std::array<char, 1'000'000> buffer_;
};

int main() {
    boost::asio::io_context io_context;
    unsigned short port = 6666;
    Server zmq;

    std::thread th(&Server::run, &zmq);
    th.detach();
    TCPServer server(io_context, port);

    io_context.run();

    return 0;
}
