#pragma once
#include <zmq.hpp>

namespace toad::communication_protocol
{
class Endpoint;
} // namespace toad::communication_protocol

namespace toad::communication_protocol::tcp
{
class Message;

class Notifier
{
  private:
    zmq::context_t context_;
    zmq::socket_t socket_;

  public:
    Notifier(const Endpoint &);
    void start();
    void send(const Message &);
};
} // namespace toad::communication_protocol::tcp