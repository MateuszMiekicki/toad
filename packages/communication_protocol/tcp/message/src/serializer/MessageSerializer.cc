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
    TRACE_LOG("Serializing message: {}", message);
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType &allocator = document.GetAllocator();
    rapidjson::Value type(serialize(message.getType()).c_str(), allocator);
    document.AddMember("type", type, allocator);
    rapidjson::Value purpose(serialize(message.getPurpose()).c_str(), allocator);
    document.AddMember("purpose", purpose, allocator);
    rapidjson::Value payload(serialize(message.getPayload()).c_str(), allocator);
    document.AddMember("payload", payload, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    return buffer.GetString();
}
} // namespace toad::communication_protocol::tcp