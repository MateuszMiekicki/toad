#pragma once
#include "toad/communication_protocol/endpoint/Endpoint.hh"
#include <boost/asio.hpp>
#include <map>
#include <memory>
#include <array>
#include "toad/communication_protocol/tcp/message/Hub.hh"

namespace toad::communication_protocol::tcp
{
class Broker
{
    private:
    Hub& hub_;
    boost::asio::io_context ioContext_;
    boost::asio::ip::tcp::acceptor acceptor_;
    using connection_t = std::shared_ptr<boost::asio::ip::tcp::socket>;
    std::map<ipAddress_t, connection_t> clients_{};
    std::array<char, 1'000'000> buffer_{};

    void listen();
    void setAcceptHandler();
    void handleClient(connection_t);
    bool handleHandshake(connection_t, std::size_t);
    void handleDisconnect(connection_t);
void setReader(connection_t );

    public:
    connection_t getConnection(const ipAddress_t&);
    void send(connection_t, const std::string&);
    Broker(Hub&,const Endpoint&);
    void start();
};
} // namespace toad::communication_protocol::mqtt
