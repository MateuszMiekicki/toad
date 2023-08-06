#include "toad/communication_protocol/tcp/requester/Requester.hh"
#include "toad/communication_protocol/tcp/Logger.hh"
#include "toad/communication_protocol/tcp/message/Hub.hh"
#include "toad/communication_protocol/tcp/message/serializer/MessageSerializer.hh"
#include "toad/communication_protocol/tcp/requester/Worker.hh"

namespace toad::communication_protocol::tcp
{
Requester::Requester(const Endpoint& endpoint, Hub& hub) :
    hub_{hub}, context_(1), frontendSocket_(context_, zmq::socket_type::router),
    backendSocket_(context_, zmq::socket_type::dealer), sender_(context_, zmq::socket_type::dealer)
{
    INFO_LOG("Requester setup on {}", endpoint);
    const auto address =
        "tcp://" + endpoint.endpoint().address().to_string() + ":" + std::to_string(endpoint.endpoint().port());
    frontendSocket_.bind(address);
    backendSocket_.bind(workerAddress_);
    sender_.connect(workerAddress_);
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
    DEBUG_LOG("All workers(number: {}) detached", numOfWorker);
    zmq::proxy(frontendSocket_, backendSocket_);
}

void Requester::send(const Message& message)
{
    [[maybe_unused]] const auto sendIdStatus =
        sender_.send(zmq::message_t(message.getClientId()), zmq::send_flags::sndmore);
    [[maybe_unused]] const auto sendResponseStatus =
        sender_.send(zmq::message_t(serialize(message)), zmq::send_flags::none);
    DEBUG_LOG("sendIdStatus: {}, sendResponseStatus: {}", sendIdStatus.value_or(0), sendResponseStatus.value_or(0));
}

Worker Requester::workerTask()
{
    Worker worker(workerAddress_, hub_, context_);
    worker.work();
    return worker;
}
} // namespace toad::communication_protocol::tcp