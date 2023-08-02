#include "toad/communication_protocol/tcp/Logger.hh"
#include "toad/communication_protocol/tcp/message/Payload.hh"
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <stdexcept>
#include <string>

namespace toad::communication_protocol::tcp
{
std::string serialize(const Payload &payload)
{
    if(payload.getType() not_eq Payload::Type::json)
    {
        throw std::runtime_error("Payload type not supported");
    }
    rapidjson::Document document;
    document.Parse(payload.getPayload().c_str());
    if(document.HasParseError())
    {
        throw std::runtime_error("Payload is not valid json");
    }
    DEBUG_LOG("Payload is {}", static_cast<int>(document.GetType()));
    if(not document.IsObject())
    {
        throw std::runtime_error("Payload must be an object");
    }
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    return buffer.GetString();
}
} // namespace toad::communication_protocol::tcp