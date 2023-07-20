#pragma once
#include "toad/communication_protocol/endpoint/Endpoint.hh"
#include "toad/communication_protocol/tcp/message/Hub.hh"
#include "toad/communication_protocol/tcp/requester/Worker.hh"
#include <map>
#include <zmq.hpp>

namespace toad::communication_protocol::tcp
{
class Requester
{
  private:
    const std::string workerAddress_ = "inproc://requester_backend";
    Hub& hub_;
    zmq::context_t context_;
    zmq::socket_t frontendSocket_;
    zmq::socket_t backendSocket_;
    zmq::socket_t sender_;
    Worker workerTask();

  public:
    Requester(const Endpoint&, Hub&);
    void start();
    void send(const Message&);
};
} // namespace toad::communication_protocol::tcp
