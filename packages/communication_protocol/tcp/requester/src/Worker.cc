#include "toad/communication_protocol/tcp/requester/Worker.hh"
#include "toad/communication_protocol/tcp/Logger.hh"
#include <chrono>
#include "toad/communication_protocol/tcp/message/Hub.hh"

namespace toad::communication_protocol::tcp
{
Worker::Worker(Hub& hub, zmq::context_t& context) : hub_{hub}, workerSocket_(context, zmq::socket_type::dealer)
{
}

void Worker::work()
{
    workerSocket_.connect("inproc://backend");
    int i = 0;
    while(true)
    {
        INFO_LOG("loop counter: {}", i);
        zmq::message_t identity;
        zmq::message_t request;

        auto idStatus = workerSocket_.recv(identity);
        auto requestStatus = workerSocket_.recv(request);
        INFO_LOG("idStatus: {}, requestStatus: {}", idStatus.value_or(0), requestStatus.value_or(0));
        std::string id = std::string(static_cast<char*>(identity.data()), identity.size());
        std::string response = std::string(static_cast<char*>(request.data()), request.size());
        auto payload = PayloadFactory::createBytes(response);
        auto message = MessageFactory::createRequest(payload);
        hub_.push(message);
        
        DEBUG_LOG("received from {}: ({})", id, response);
        response = std::string("dupda");
        
        zmq::message_t replyResponse(response.size());
        memcpy(replyResponse.data(), response.data(), response.size());

        auto sendIdStatus = workerSocket_.send(identity, zmq::send_flags::sndmore);
        auto sendResponseStatus = workerSocket_.send(replyResponse, zmq::send_flags::none);
        INFO_LOG("sendIdStatus: {}, sendResponseStatus: {}", sendIdStatus.value_or(0), sendResponseStatus.value_or(0));
        ++i;
        }
}
} // namespace toad::communication_protocol::tcp