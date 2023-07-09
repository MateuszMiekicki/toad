#pragma once
#include "toad/communication_protocol/endpoint/Endpoint.hh"
#include <zmq.hpp>
#include "toad/communication_protocol/tcp/message/Hub.hh"

namespace toad::communication_protocol::tcp
{
class Requester
{
private:
    Hub& hub_; 
    zmq::context_t context_;
    zmq::socket_t frontendSocket_;
    zmq::socket_t backendSocket_;
  public:
    Requester(Hub&);

    void start();
  private:
    void workerTask();
    std::vector<std::thread> workers{};

};
} // namespace toad::communication_protocol::mqtt
