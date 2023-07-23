#include "toad/communication_protocol/tcp/requester/Worker.hh"
#include "toad/communication_protocol/tcp/Logger.hh"
#include <chrono>

namespace
{
[[maybe_unused]] std::string convertRecvBufferResultToPrintable(const zmq::recv_result_t& result)
{
    if(result.has_value())
    {
        return std::to_string(result.value());
    }
    else
    {
        return "recv_buffer_result_t is empty";
    }
}

std::string zmqMessageToString(const zmq::message_t& message)
{
    return std::string(static_cast<const char*>(message.data()), message.size());
}
} // namespace

namespace toad::communication_protocol::tcp
{
Worker::Worker(const std::string& workerAddress, Hub& hub, zmq::context_t& context) :
    hub_{hub}, workerSocket_(context, zmq::socket_type::dealer)
{
    connect(workerAddress);
}

void Worker::connect(const std::string& workerAddress)
{
    try
    {
        workerSocket_.connect(workerAddress);
    }
    catch(const zmq::error_t& e)
    {
        ERROR_LOG("Woker connection exception [zmq::error_t]: {}", e.what());
    }
    catch(const std::exception& e)
    {
        ERROR_LOG("Woker connection exception [std::exception] {}", e.what());
    }
    catch(...)
    {
        ERROR_LOG("Woker connection exception: UNKNOWN EXCEPTION");
    }
}

void Worker::handleConnection()
{
    while(true)
    {
        zmq::message_t identity;
        zmq::message_t request;

        [[maybe_unused]] const auto identityRecvBufferResult = workerSocket_.recv(identity);
        [[maybe_unused]] const auto requestRecvBufferResult = workerSocket_.recv(request);
        DEBUG_LOG("identityRecvBufferResult: {}, requestRecvBufferResult: {}",
                  convertRecvBufferResultToPrintable(identityRecvBufferResult),
                  convertRecvBufferResultToPrintable(requestRecvBufferResult));
        if(!identityRecvBufferResult.has_value() || !requestRecvBufferResult.has_value())
        {
            ERROR_LOG("Worker::handleConnection: recv failed");
            continue;
        }
        const auto payload = PayloadFactory::createJson(zmqMessageToString(request));
        const auto message = MessageFactory::createRequest(zmqMessageToString(identity), payload);
        TRACE_LOG("Worker::handleConnection: {} {}", zmqMessageToString(identity), payload.getPayload());

        hub_.push(message);
    }
}

void Worker::work()
{
    handleConnection();
}
} // namespace toad::communication_protocol::tcp