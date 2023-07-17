#include "toad/communication_protocol/tcp/requester/Requester.hh"
#include "toad/communication_protocol/tcp/Logger.hh"
#include "toad/communication_protocol/tcp/message/Hub.hh"
#include "toad/communication_protocol/tcp/requester/Worker.hh"

namespace toad::communication_protocol::tcp
{
Requester::Requester(Hub& hub) :
    hub_{hub}, context_(1), frontendSocket_(context_, zmq::socket_type::router),
    backendSocket_(context_, zmq::socket_type::dealer), sender_(context_, zmq::socket_type::dealer)
{
    INFO_LOG("Requester  setup on {}", "5571");
    frontendSocket_.bind("tcp://*:5571");
    backendSocket_.bind("inproc://backend");
    sender_.connect("inproc://backend");
}

void Requester::start()
{
    const auto numOfWorker = 5;
    auto workers = std::vector<std::thread>();
    workers.reserve(numOfWorker);
    std::generate_n(std::back_inserter(workers),
                    numOfWorker,
                    [this]()
                    {
        return std::thread(&Requester::workerTask, this);
    });

    std::for_each(workers.begin(),
                  workers.end(),
                  [](auto& worker)
                  {
        worker.detach();
    });
    zmq::proxy(frontendSocket_, backendSocket_);
}

void Requester::send(const Message& message)
{
    auto sendIdStatus = sender_.send(zmq::message_t(message.clientId_), zmq::send_flags::sndmore);
    auto sendResponseStatus = sender_.send(zmq::message_t(message.payload_.payload), zmq::send_flags::none);
    INFO_LOG("sendIdStatus: {}, sendResponseStatus: {}", sendIdStatus.value_or(0), sendResponseStatus.value_or(0));
}

Worker Requester::workerTask()
{
    Worker worker(hub_, context_);
    worker.work();
    return worker;
}
} // namespace toad::communication_protocol::tcp