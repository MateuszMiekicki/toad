#include "toad/communication_protocol/tcp/notifier/notifier.hh"
#include "toad/communication_protocol/endpoint/Endpoint.hh"
#include "toad/communication_protocol/tcp/Logger.hh"
#include "toad/communication_protocol/tcp/message/Message.hh"

namespace toad::communication_protocol::tcp
{
Notifier::Notifier(const Endpoint& endpoint) : context_(1), socket_(context_, zmq::socket_type::push)
{
    INFO_LOG("Notifier setup on {}", endpoint);
    const auto address =
        "tcp://" + endpoint.endpoint().address().to_string() + ":" + std::to_string(endpoint.endpoint().port());
    socket_.bind(address);
}

void Notifier::start()
{
}

void Notifier::send(const Message& message)
{
    [[maybe_unused]] const auto sendResponseStatus =
        socket_.send(zmq::message_t(message.payload_.getPayload()), zmq::send_flags::none);
    DEBUG_LOG("sendResponseStatus: {}", sendResponseStatus.value_or(0));
}
} // namespace toad::communication_protocol::tcp

// Requester::Requester(const Endpoint& endpoint, Hub& hub) :
//     hub_{hub}, context_(1), frontendSocket_(context_, zmq::socket_type::router),
//     backendSocket_(context_, zmq::socket_type::dealer), sender_(context_, zmq::socket_type::dealer)