#include "toad/communication_protocol/tcp/broker/Broker.hh"
#include "toad/communication_protocol/tcp/Logger.hh"

namespace toad::communication_protocol::tcp
{
namespace
{
    std::string findClientId(const  Broker::clients_t , const Broker::connection_t& )
    {
        // auto pos = message.find("clientId");
        // if(pos == std::string::npos)
        // {
        //     return std::nullopt;
        // }
        // auto start = message.find("\"", pos);
        // auto end = message.find("\"", start + 1);
        // return message.substr(start + 1, end - start - 1);
        return "test";
    }
}

Broker::Broker(Hub& hub, const Endpoint& endpoint) : hub_{hub}, ioContext_{}, acceptor_(ioContext_, endpoint.endpoint())
{
    INFO_LOG("TCP broker setup on {}", endpoint);
}

void Broker::handleDisconnect(connection_t)
{
    DEBUG_LOG("Client disconnected");
}

void Broker::listen()
{
    ioContext_.run();
}

void Broker::setAcceptHandler()
{
    auto newConnection = std::make_shared<boost::asio::ip::tcp::socket>(acceptor_.get_executor());

    acceptor_.async_accept(*newConnection,
                           [this, newConnection](const boost::system::error_code& error)
                           {
        if(!error)
        {
            handleClient(newConnection);
        }

        setAcceptHandler();
    });
}

bool Broker::handleHandshake(connection_t socket, std::size_t length)
{
    std::string message(buffer_.data(), length - 1);
    DEBUG_LOG("Handshake: {}", message);
    if(clients_.find(message) != clients_.end())
    {
        WARN_LOG("Client {} already connected", message);
        return false;
    }
    clients_[message] = socket;
    return true;
}

void Broker::setReader(connection_t socket)
{
    socket->async_read_some(boost::asio::buffer(buffer_),
                            [this, socket](const boost::system::error_code& error, std::size_t bytes_transferred)
                            {
        if(!error)
        {
            DEBUG_LOG("Received data: {}", std::string(buffer_.data(), bytes_transferred));
            auto payload = PayloadFactory::createJson(std::string(buffer_.data(), bytes_transferred));
            auto msg = MessageFactory::createAlert(findClientId(clients_, socket), payload);
            hub_.push(msg);
            setReader(socket);
        }
        else
        {
            WARN_LOG("Error during handshake: {}", error.message());
            handleDisconnect(socket);
        }
    });
}

void Broker::send(connection_t socket, const std::string& message)
{
    boost::asio::post(socket->get_executor(),
                      [this, socket, message]()
                      {
        socket->async_write_some(boost::asio::buffer(message),
                                 [this, socket](const boost::system::error_code& error, std::size_t)
                                 {
            if(error)
            {
                handleDisconnect(socket);
            }
        });
    });
}

void Broker::handleClient(connection_t socket)
{
    INFO_LOG("New connection");

    socket->async_read_some(boost::asio::buffer(buffer_),
                            [this, socket](const boost::system::error_code& error, std::size_t bytes_transferred)
                            {
        if(!error)
        {
            if(handleHandshake(socket, bytes_transferred))
            {
                setReader(socket);
            }
            else
            {
                send(socket, "Client already connected");
                socket->close();
            }
        }
        else
        {
            handleDisconnect(socket);
        }
    });
}

void Broker::start()
{
    INFO_LOG("Starting tcp broker");
    setAcceptHandler();
    listen();
}
} // namespace toad::communication_protocol::tcp