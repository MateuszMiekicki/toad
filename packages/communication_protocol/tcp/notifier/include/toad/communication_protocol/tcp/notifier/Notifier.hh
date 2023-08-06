#pragma once
#include "toad/communication_protocol/tcp/interface/Sender.hh"
#include "toad/communication_protocol/tcp/interface/Server.hh"
#include <zmq.hpp>

namespace toad::communication_protocol
{
class Endpoint;
} // namespace toad::communication_protocol

namespace toad::communication_protocol::tcp
{
class Message;

class Notifier : public interface::Sender, public interface::Server
{
  private:
    zmq::context_t context_;
    zmq::socket_t socket_;

  public:
    Notifier(const Endpoint &);
    virtual ~Notifier() = default;

    void start() override;
    virtual void send(const Message &) override;
};
} // namespace toad::communication_protocol::tcp