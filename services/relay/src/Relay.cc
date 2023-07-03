#include "toad/services/relay/Logger.hh"
#include <atomic>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <mutex>
#include <thread>
#include <vector>
#include <zmq.hpp>

using boost::asio::ip::tcp;

std::string longFOO(int t)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(t));
    return "udalo sie";
}

class TCPServer
{
  public:
    TCPServer(boost::asio::io_context& io_context, unsigned short port) :
        acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
    {
        startAccept();
    }

    void startAccept()
    {
        auto newConnection = std::make_shared<tcp::socket>(acceptor_.get_executor());

        acceptor_.async_accept(*newConnection,
                               [this, newConnection](const boost::system::error_code& error)
                               {
            if(!error)
            {
                handleClient(std::move(newConnection));
            }

            startAccept();
        });
    }

    void handleClient(std::shared_ptr<tcp::socket> socket)
    {
        DEBUG_LOG("New connection");

        socket->async_read_some(boost::asio::buffer(buffer_),
                                [this, socket](const boost::system::error_code& error, std::size_t bytes_transferred)
                                {
            if(!error)
            {
                handleHandshake(socket, bytes_transferred);
            }
            else
            {
                handleDisconnect(socket);
            }
        });
    }

    void handleHandshake(std::shared_ptr<tcp::socket> socket, std::size_t length)
    {
        std::string message(buffer_.data(), length - 1);
        DEBUG_LOG("Handshake: {}", message);
        clients_[message] = socket;
        socket->async_read_some(boost::asio::buffer(buffer_),
                                [this, socket](const boost::system::error_code& error, std::size_t bytes_transferred)
                                {
            if(!error)
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

    void setDefaultRec(std::shared_ptr<tcp::socket> socket)
    {
        socket->async_read_some(boost::asio::buffer(buffer_),
                                [this, socket](const boost::system::error_code& error, std::size_t bytes_transferred)
                                {
            if(!error)
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

    void handleReceivedData(std::shared_ptr<tcp::socket> socket, std::size_t length)
    {
        std::string message(buffer_.data(), length);
        TRACE_LOG("Message received: {}", message);

        std::thread th(
            [this, socket, message]()
            {
            auto r = std::string();
            try
            {
                r = longFOO(std::stoi(message));
            }
            catch(const std::exception& e)
            {
                r = message;
            }
            TRACE_LOG("Message send: {}", r);

            boost::asio::post(socket->get_executor(),
                              [this, socket, r]()
                              {
                socket->async_write_some(
                    boost::asio::buffer(r),
                    [this, socket](const boost::system::error_code& error, std::size_t bytes_transferred)
                    {
                    if(!error)
                    {
                    }
                    else
                    {
                        handleDisconnect(socket);
                    }
                    });
            });
        });
        th.detach();

        setDefaultRec(socket);
    }

    void handleDisconnect(std::shared_ptr<tcp::socket> socket)
    {
        DEBUG_LOG("Client disconnected");
    }

    tcp::acceptor acceptor_;
    std::array<char, 1'000'000> buffer_;

  public:
    std::map<std::string, std::shared_ptr<tcp::socket>> clients_;
};

std::atomic_int id{0};

class Worker
{
  public:
    int id_;
    TCPServer& tcp;

    Worker(TCPServer& ser, zmq::context_t& context) : tcp{ser}, workerSocket_(context, ZMQ_DEALER)
    {
        id_ = id++;
        const auto size = 1'000'000;
        workerSocket_.setsockopt(ZMQ_RCVBUF, &size, sizeof(size));
    }

    void work()
    {
        workerSocket_.connect("inproc://backend");

        while(true)
        {
            zmq::message_t identity;
            zmq::message_t request;

            workerSocket_.recv(&identity);
            workerSocket_.recv(&request);
            std::string id = std::string(static_cast<char*>(identity.data()), identity.size());
            std::string response = std::string(static_cast<char*>(request.data()), request.size());

            DEBUG_LOG("Worker {} received from {}: ({}) {}", id_, id, response.size(), response);
            if(tcp.clients_.find(id) != tcp.clients_.end())
            {
                auto tcpClient = tcp.clients_[id].get();
                tcpClient->write_some(boost::asio::buffer(response));
            }
            else
            {
                WARN_LOG("Client {} not found", id);
                workerSocket_.send(identity, ZMQ_SNDMORE);
                response = "client not found";
                zmq::message_t replyResponse(response.size());
                memcpy(replyResponse.data(), response.data(), response.size());
                INFO_LOG("test3");
                workerSocket_.send(replyResponse);
                break;
            }
            auto tcpClientsh = tcp.clients_[id];
            auto tcpClient = tcpClientsh.get();
            boost::asio::streambuf resp;
            response = std::string("dupda");
            {
                std::array<char, 1000> buf;
                boost::system::error_code ec;
                auto size =
                    boost::asio::read(*tcpClient, boost::asio::buffer(buf), boost::asio::transfer_at_least(1), ec);
                if(ec)
                {
                    // An error occurred.
                }
                else
                {
                    response = std::string(std::begin(buf), size);
                }
            }
            zmq::message_t replyResponse(response.size());
            memcpy(replyResponse.data(), response.data(), response.size());

            workerSocket_.send(identity, ZMQ_SNDMORE);
            workerSocket_.send(replyResponse);

            tcp.setDefaultRec(tcpClientsh);
        }
    }

  private:
    zmq::socket_t workerSocket_;
};

class Server
{
    TCPServer& tcp;

  public:
    Server(TCPServer& ser) :
        tcp{ser}, context_(1), frontendSocket_(context_, ZMQ_ROUTER), backendSocket_(context_, ZMQ_DEALER)
    {
    }

    void run()
    {
        frontendSocket_.bind("tcp://*:5570");
        backendSocket_.bind("inproc://backend");

        std::vector<std::thread> workerThreads;
        for(int i = 0; i < kNumWorkers; ++i)
        {
            workerThreads.emplace_back(
                [this]()
                {
                workerTask();
            });
        }

        zmq::proxy(static_cast<void*>(frontendSocket_), static_cast<void*>(backendSocket_), nullptr);

        for(auto& thread: workerThreads)
        {
            thread.join();
        }
    }

  private:
    static constexpr int kNumWorkers = 5;

    zmq::context_t context_;
    zmq::socket_t frontendSocket_;
    zmq::socket_t backendSocket_;

    void workerTask()
    {
        Worker worker(tcp, context_);
        worker.work();
    }
};

int main()
{
    boost::asio::io_context io_context;
    unsigned short port = 6666;
    TCPServer server(io_context, port);
    Server zmq(server);

    std::thread th(&Server::run, &zmq);
    th.detach();

    io_context.run();

    return 0;
}
