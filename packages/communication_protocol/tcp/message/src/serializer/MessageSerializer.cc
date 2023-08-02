#include "toad/communication_protocol/tcp/message/serializer/MessageSerializer.hh"
#include "toad/communication_protocol/tcp/Logger.hh"
#include "toad/communication_protocol/tcp/message/Message.hh"
#include "toad/communication_protocol/tcp/message/serializer/PayloadSerializer.hh"
#include "toad/communication_protocol/tcp/message/serializer/PurposeSerializer.hh"
#include "toad/communication_protocol/tcp/message/serializer/TypeSerializer.hh"
#include <rapidjson/allocators.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <string>

namespace toad::communication_protocol::tcp
{
std::string serialize(const Message &message)
{
    DEBUG_LOG("Serializing message: {}", message);
    TRACE_LOG("Raw payload: {}", message.getRawPayload());

    const auto type = R"("type":")" + serialize(message.getType()) + R"(")";
    const auto purpose = R"("purpose":")" + serialize(message.getPurpose()) + R"(")";
    const auto payload = R"("payload":)" + serialize(message.getPayload());
    const auto stringToParse = R"({)" + type + R"(,)" + purpose + R"(,)" + payload + R"(})";
    TRACE_LOG("String to parse: {}", stringToParse);
    rapidjson::Document document;
    document.Parse(stringToParse.c_str());
    if(document.HasParseError())
    {
        throw std::runtime_error("Message is not valid json");
    }
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    const auto serializedMessage = buffer.GetString();
    TRACE_LOG("Serialized message: {}", serializedMessage);
    return serializedMessage;
}
} // namespace toad::communication_protocol::tcp