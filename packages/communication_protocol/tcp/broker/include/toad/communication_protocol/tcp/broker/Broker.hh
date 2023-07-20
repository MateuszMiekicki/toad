#pragma once
#include "toad/communication_protocol/endpoint/Endpoint.hh"
#include "toad/communication_protocol/tcp/message/Hub.hh"
#include <array>
#include <boost/asio.hpp>
#include <map>
#include <memory>

namespace toad::communication_protocol::tcp
{
class Broker
{
  public:
    using macAddress_t = std::string;
    using connection_t = std::shared_ptr<boost::asio::ip::tcp::socket>;
    using clients_t = std::map<macAddress_t, connection_t>;

  private:
    Hub& hub_;
    boost::asio::io_context ioContext_;
    boost::asio::ip::tcp::acceptor acceptor_;
    clients_t clients_{};
    std::array<char, 1'000'000> buffer_{};

    void listen();
    void setAcceptHandler();
    void handleClient(connection_t);
    bool handleHandshake(connection_t, std::size_t);
    void handleDisconnect(connection_t);
    void setReader(connection_t);
    void send(connection_t, const std::string&);

  public:
    connection_t getConnection(const ipAddress_t&);
    void send(const Message&);
    Broker(const Endpoint&, Hub&);
    void start();
};
} // namespace toad::communication_protocol::tcp
