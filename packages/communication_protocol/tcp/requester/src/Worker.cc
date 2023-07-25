#include "toad/communication_protocol/tcp/requester/Worker.hh"
#include "toad/communication_protocol/tcp/Logger.hh"
#include <chrono>
#include <rapidjson/document.h>
#include <rapidjson/error/en.h>

namespace toad::communication_protocol::tcp
{
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

Message buildMessage(const zmq::message_t& identity, const rapidjson::Document& document)
{
    const auto messageType = Message::deserializeType(document["type"].GetString());
    const auto messagePurpose = Message::deserializePurpose(document["purpose"].GetString());
    const auto payload = PayloadFactory::createJson(document["payload"].GetString());
    return {zmqMessageToString(identity), messageType, messagePurpose, payload};
}
} // namespace

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
        const auto payload = zmqMessageToString(request);
        rapidjson::Document document;
        document.Parse(payload.c_str());
        if(document.HasParseError())
        {
            ERROR_LOG("Worker::handleConnection: JSON parse error: {}",
                      rapidjson::GetParseError_En(document.GetParseError()));
            continue;
        }
        if(!document.HasMember("type") || !document.HasMember("purpose") || !document.HasMember("payload"))
        {
            ERROR_LOG("Worker::handleConnection: Received message without type or purpose or payload");
            continue;
        }
        const auto message = buildMessage(identity, document);
        TRACE_LOG("Worker::handleConnection: {} {}", message.getClientId(), message.getRawPayload());
        hub_.push(message);
    }
}

void Worker::work()
{
    handleConnection();
}
} // namespace toad::communication_protocol::tcp