#pragma once
#include "toad/communication_protocol/tcp/message/Hub.hh"
#include <zmq.hpp>

namespace toad::communication_protocol::tcp
{
class Worker
{
  private:
    Hub& hub_;
    zmq::socket_t workerSocket_;
    void connect(const std::string&);
    void handleConnection();

  public:
    Worker(const std::string&, Hub&, zmq::context_t&);
    void work();
};
} // namespace toad::communication_protocol::tcp