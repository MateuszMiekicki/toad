#include "toad/communication_protocol/tcp/requester/Requester.hh"
#include "toad/communication_protocol/tcp/requester/Worker.hh"
#include "toad/communication_protocol/tcp/message/Hub.hh"

namespace toad::communication_protocol::tcp
{
Requester::Requester(Hub& hub) :hub_{hub}, context_(1), frontendSocket_(context_, zmq::socket_type::router), 
backendSocket_(context_, zmq::socket_type::dealer)
{
        frontendSocket_.bind("tcp://*:5571");
        backendSocket_.bind("inproc://backend");
}

void Requester::start()
{
    for (int i = 0; i < 5; ++i)
    {
            workers.emplace_back(
                [this]()
                {
                workerTask();
            });    
    }

    zmq::proxy(frontendSocket_, backendSocket_);
}
void Requester::workerTask()
{
    Worker worker(hub_, context_);
    worker.work();
}
} // namespace toad::communication_protocol::tcp    