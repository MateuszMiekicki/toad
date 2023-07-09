#pragma once
#include "toad/communication_protocol/tcp/message/Identifier.hh"

namespace toad::communication_protocol::tcp
{
struct Payload
{
    const std::string payload;
    enum class Type
    {
        unknown,
        proto,
        json,
        bytes,
    };
    const Type type;
};

struct Message
{
    const MessageId id_;
    enum class Type
    {
        unknown,
        request,
        response,
        alert,
    };
    const Type type_;
    
    const Payload payload_;
    Message(const Type& type, const Payload &payload) :
        id_{}, type_{type}, payload_{payload}
    {
    }
};
class PayloadFactory
{
    public:
        static Payload createProto(const std::string &payload)
        {
            return Payload{payload, Payload::Type::proto};
        }
        static Payload createJson(const std::string &payload)
        {
            return Payload{payload, Payload::Type::json};
        }
        static Payload createBytes(const std::string &payload)
        {
            return Payload{payload, Payload::Type::bytes};
        }
};
class MessageFactory
{
  public:
    static Message createRequest(const Payload &payload)
    {
        return Message{Message::Type::request, payload};
    }
    static Message createResponse(const Payload &payload)
    {
        return Message{Message::Type::response, payload};
    }
    static Message createAlert(const Payload &payload)
    {
        return Message{Message::Type::alert, payload};
    }
};
} // namespace toad::communication_protocol::tcp
