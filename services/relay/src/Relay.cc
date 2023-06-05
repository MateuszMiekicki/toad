#include <iostream>
#include <string>
#include <unordered_map>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class TcpServer {
public:
    TcpServer(boost::asio::io_context& io_context, short port)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
    {
        doAccept();
    }

private:
    void doAccept()
    {
        acceptor_.async_accept(
            [this](boost::system::error_code ec, tcp::socket socket)
            {
                if (!ec)
                {
                    std::make_shared<Session>(std::move(socket), macAddressMap_)->start();
                }

                doAccept();
            });
    }

    class Session : public std::enable_shared_from_this<Session> {
    public:
        Session(tcp::socket socket, std::unordered_map<std::string, tcp::socket*>& macAddressMap)
            : socket_(std::move(socket)), macAddressMap_(macAddressMap)
        {
        }

        void start()
        {
            doReadHandshake();
        }

    private:
        void doReadHandshake()
        {
            auto self(shared_from_this());
            boost::asio::async_read_until(
                socket_,
                boost::asio::dynamic_buffer(handshakeBuffer_),
                '\n',
                [this, self](boost::system::error_code ec, std::size_t length)
                {
                    if (!ec)
                    {
                        std::cout<<handshakeBuffer_;
                        std::string macAddress = handshakeBuffer_.substr(0, length - 1); // -1 to exclude newline character
                        std::cout<<"macAddress "<<macAddress;
                        macAddressMap_[macAddress] = &socket_;
                        doRead();
                    }
                    else
                    {
                        std::cerr << "Error during handshake: " << ec.message() << std::endl;
                    }
                });
        }

        void doRead()
        {
            auto self(shared_from_this());
            socket_.async_read_some(
                boost::asio::buffer(readBuffer_),
                [this, self](boost::system::error_code ec, std::size_t length)
                {
                    if (!ec)
                    {
                        processReceivedData(length);
                        doRead();
                    }
                    else
                    {
                        std::cerr << "Error during read: " << ec.message() << std::endl;
                    }
                });
        }

        void processReceivedData(std::size_t length)
        {
            std::string receivedData(readBuffer_.data(), length);
            // Do something with the received data
            std::cout<<receivedData;
            // Example: Splitting the received data into MAC address and message
            std::size_t delimiterPos = receivedData.find(':');
            if (delimiterPos != std::string::npos)
            {
                std::string macAddress = receivedData.substr(0, delimiterPos);
                std::string message = receivedData.substr(delimiterPos + 1);

                send(macAddress, message);
            }
        }

        void send(const std::string& macAddress, const std::string& message)
        {
            auto it = macAddressMap_.find(macAddress);
            if (it != macAddressMap_.end())
            {
                tcp::socket* destinationSocket = it->second;

                boost::asio::async_write(
                    *destinationSocket,
                    boost::asio::buffer(message + '\n'),
                    [](boost::system::error_code ec, std::size_t /*length*/)
                    {
                        if (ec)
                        {
                            std::cerr << "Error during send: " << ec.message() << std::endl;
                        }
                    });
            }
            else
            {
                std::cerr << "Unknown MAC address: " << macAddress << std::endl;
            }
        }

        tcp::socket socket_;
        std::string handshakeBuffer_;
        std::array<char, 1024> readBuffer_;
        std::unordered_map<std::string, tcp::socket*>& macAddressMap_;
    };

    tcp::acceptor acceptor_;
    std::unordered_map<std::string, tcp::socket*> macAddressMap_;
};

int main()
{
    try
    {
        boost::asio::io_context io_context;
        TcpServer server(io_context, 6666);
        io_context.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
