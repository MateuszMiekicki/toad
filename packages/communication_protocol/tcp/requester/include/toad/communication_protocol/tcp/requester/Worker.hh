#pragma once
#include <zmq.hpp>
#include "toad/communication_protocol/tcp/message/Hub.hh"

namespace toad::communication_protocol::tcp
{
class Worker
{
    private:
    Hub& hub_;
        zmq::socket_t workerSocket_;

  public:
    Worker(Hub&, zmq::context_t&);
    void work();
};
}