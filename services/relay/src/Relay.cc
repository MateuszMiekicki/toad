#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

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

                startAccept(); // Kolejne akceptowanie połączeń
            });
    }

    void handleClient(std::shared_ptr<tcp::socket> socket) {
        std::cout << "Nowe połączenie" << std::endl;

        // Odbierz pierwszą wiadomość (handshake)
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
        std::cout << "Odebrano handshake: " << message << std::endl;

        // Przetwarzaj handshake

        // Kontynuuj odbieranie danych od klienta
        socket->async_read_some(boost::asio::buffer(buffer_),
            [this, socket](const boost::system::error_code& error, std::size_t bytes_transferred) {
                if (!error) {
                    handleReceivedData(socket, bytes_transferred);
                } else {
                    handleDisconnect(socket);
                }
            });
    }

    void handleReceivedData(std::shared_ptr<tcp::socket> socket, std::size_t length) {
        std::string message(buffer_.data(), length);
        std::cout << "Odebrano wiadomość: " << message << std::endl;

        // Przetwarzaj odebrane dane

        // Odpowiedz do klienta (opcjonalnie)
        // std::string response = "Odpowiedź serwera";
        // socket->async_write_some(boost::asio::buffer(response),
        //     [this, socket](const boost::system::error_code& error, std::size_t bytes_transferred) {
        //         if (!error) {
        //             // Obsłużono wysłanie odpowiedzi
        //         } else {
        //             handleDisconnect(socket);
        //         }
        //     });

        // Kontynuuj odbieranie danych od klienta
        socket->async_read_some(boost::asio::buffer(buffer_),
            [this, socket](const boost::system::error_code& error, std::size_t bytes_transferred) {
                if (!error) {
                    handleReceivedData(socket, bytes_transferred);
                } else {
                    handleDisconnect(socket);
                }
            });
    }

    void handleDisconnect(std::shared_ptr<tcp::socket> socket) {
        std::cout << "Rozłączono klienta" << std::endl;
    }

    tcp::acceptor acceptor_;
    std::array<char, 1024> buffer_;
};

int main() {
    boost::asio::io_context io_context;
    unsigned short port = 6666;

    TCPServer server(io_context, port);

    io_context.run();

    return 0;
}
