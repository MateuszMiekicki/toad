#include "toad/communication_protocol/tcp/broker/Broker.hh"
#include "toad/communication_protocol/tcp/Logger.hh"
#include <rapidjson/document.h>

namespace toad::communication_protocol::tcp
{
namespace
{
std::string findClientId(const Broker::clients_t clients, const Broker::connection_t& connection)
{
    for(const auto& client: clients)
    {
        if(client.second == connection)
        {
            return client.first;
        }
    }
    return {};
}
} // namespace

Broker::Broker(Hub& hub, const Endpoint& endpoint) : hub_{hub}, ioContext_{}, acceptor_(ioContext_, endpoint.endpoint())
{
    //todo: problem with formatter 
    INFO_LOG("TCP broker setup on {}", "endpoint");
}

void Broker::handleDisconnect(connection_t connection)
{
    auto clientId = findClientId(clients_, connection);
    clients_.erase(clientId);
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
            const auto recivedData = std::string(buffer_.data(), bytes_transferred - 1);
            DEBUG_LOG("Received data: {}", recivedData);
            rapidjson::Document document;
            document.Parse(recivedData.c_str());
            if(document.HasParseError())
            {
                WARN_LOG("Parse error: {}", "document.GetParseError()");
                setReader(socket);
                return;
            }
            if(document.HasMember("type"))
            {
                auto convertTypeToEnum = [](std::string type)
                {
                    std::transform(type.begin(),
                                   type.end(),
                                   type.begin(),
                                   [](unsigned char c)
                                   {
                        return std::tolower(c);
                    });
                    if(type == "response")
                    {
                        return Message::Type::response;
                    }
                    else if(type == "alert")
                    {
                        return Message::Type::alert;
                    }
                    else
                    {
                        return Message::Type::unknown;
                    }
                }(document["type"].GetString());
                auto payload = PayloadFactory::createJson(std::move(recivedData));
                hub_.push(Message(findClientId(clients_, socket), convertTypeToEnum, payload));
            }
            else
            {
                WARN_LOG("Received message without type");
            }

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

void Broker::send(const Message& message)
{
    auto clientId = message.clientId_;
    if(clients_.find(clientId) == clients_.end())
    {
        WARN_LOG("Client {} not connected", clientId);
        return;
    }
    send(clients_[clientId], message.payload_.payload);
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