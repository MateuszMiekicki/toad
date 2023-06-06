#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <thread>
#include "toad/services/relay/Logger.hh"

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

    TCPServer server(io_context, port);

    io_context.run();

    return 0;
}
