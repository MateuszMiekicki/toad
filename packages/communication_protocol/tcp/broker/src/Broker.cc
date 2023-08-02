#include "toad/communication_protocol/tcp/broker/Broker.hh"
#include "toad/communication_protocol/tcp/Logger.hh"
#include "toad/communication_protocol/tcp/message/serializer/MessageSerializer.hh"
#include <rapidjson/document.h>
#include <rapidjson/error/en.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

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

std::string toString(const rapidjson::Value& document)
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    return buffer.GetString();
}
} // namespace

Broker::Broker(const Endpoint& endpoint, Hub& hub) : hub_{hub}, ioContext_{}, acceptor_(ioContext_, endpoint.endpoint())
{
    INFO_LOG("TCP broker setup on {}", endpoint);
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
    const auto macAddress = std::string(buffer_.data(), length);
    DEBUG_LOG("Recived handshake: {}", macAddress);
    if(clients_.find(macAddress) != clients_.end())
    {
        WARN_LOG("Client {} already connected", macAddress);
        return false;
    }
    clients_[macAddress] = socket;
    return true;
}

void Broker::setReader(connection_t socket)
{
    socket->async_read_some(boost::asio::buffer(buffer_),
                            [this, socket](const boost::system::error_code& error, std::size_t bytes_transferred)
                            {
        if(!error)
        {
            const auto recivedData = std::string(buffer_.data(), bytes_transferred);
            TRACE_LOG("Received data: {}", recivedData);
            rapidjson::Document document;
            document.Parse(recivedData.c_str());
            if(document.HasParseError())
            {
                WARN_LOG("Parse error: {}", GetParseError_En(document.GetParseError()));
                setReader(socket);
                return;
            }
            if(document.HasMember("type") and document.HasMember("purpose") and document.HasMember("payload"))
            {
                const auto messageType = Message::deserializeType(document["type"].GetString());
                const auto messagePurpose = Message::deserializePurpose(document["purpose"].GetString());
                const auto payload = PayloadFactory::createJson(toString(document["payload"]));
                const auto message = Message(findClientId(clients_, socket), messageType, messagePurpose, payload);
                DEBUG_LOG("TCP broker received message: {}", message);
                hub_.push(message);
            }
            else
            {
                WARN_LOG("Received message without type or purpose or payload");
            }

            setReader(socket);
        }
        else
        {
            WARN_LOG("Error: {}", error.message());
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
        throw std::runtime_error("Client not connected");
        return;
    }
    send(clients_[clientId], serialize(message));
}

void Broker::handleClient(connection_t socket)
{
    DEBUG_LOG("New connection");
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
    INFO_LOG("Starting TCP broker");
    setAcceptHandler();
    listen();
}
} // namespace toad::communication_protocol::tcp