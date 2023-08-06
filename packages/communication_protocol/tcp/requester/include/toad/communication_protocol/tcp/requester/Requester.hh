#pragma once
#include "toad/communication_protocol/endpoint/Endpoint.hh"
#include "toad/communication_protocol/tcp/interface/Sender.hh"
#include "toad/communication_protocol/tcp/interface/Server.hh"
#include "toad/communication_protocol/tcp/message/Hub.hh"
#include "toad/communication_protocol/tcp/requester/Worker.hh"
#include <map>
#include <zmq.hpp>

namespace toad::communication_protocol::tcp
{
class Requester : public interface::Sender, public interface::Server
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
    virtual ~Requester() = default;

    void start() override;
    void send(const Message&) override;
};
} // namespace toad::communication_protocol::tcp
