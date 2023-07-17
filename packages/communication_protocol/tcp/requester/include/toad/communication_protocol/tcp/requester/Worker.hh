#pragma once
#include "toad/communication_protocol/tcp/message/Hub.hh"
#include <map>
#include <zmq.hpp>

namespace toad::communication_protocol::tcp
{
class Worker
{
  private:
    Hub& hub_;
    zmq::socket_t workerSocket_;
    void connect();
    void handleConnection();

  public:
    Worker(Hub&, zmq::context_t&);
    void work();
};
} // namespace toad::communication_protocol::tcp