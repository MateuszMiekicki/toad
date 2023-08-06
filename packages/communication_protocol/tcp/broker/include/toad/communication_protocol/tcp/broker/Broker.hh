#pragma once
#include "toad/communication_protocol/endpoint/Endpoint.hh"
#include "toad/communication_protocol/tcp/interface/Sender.hh"
#include "toad/communication_protocol/tcp/interface/Server.hh"
#include "toad/communication_protocol/tcp/message/Hub.hh"
#include <array>
#include <boost/asio.hpp>
#include <map>
#include <memory>

namespace toad::communication_protocol::tcp
{
class Broker : public interface::Sender, public interface::Server
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
    Broker(const Endpoint&, Hub&);
    virtual ~Broker() = default;

    virtual void send(const Message&) override;
    void start() override;

    connection_t getConnection(const ipAddress_t&);
};
} // namespace toad::communication_protocol::tcp
