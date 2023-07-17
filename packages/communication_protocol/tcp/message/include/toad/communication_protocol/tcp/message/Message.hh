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

using clientId_t = std::string;

struct Message
{
    const MessageId id_;
    const clientId_t clientId_;
    enum class Type
    {
        unknown,
        request,
        response,
        alert,
    };
    const Type type_;

    const Payload payload_;

    Message(const clientId_t &clientId, const Type &type, const Payload &payload) :
        id_{}, clientId_{clientId}, type_{type}, payload_{payload}
    {
    }
};

class PayloadFactory
{
  public:
    static Payload createJson(const std::string &payload)
    {
        return Payload{payload, Payload::Type::json};
    }
};

class MessageFactory
{
  public:
    static Message createRequest(const clientId_t &clientId, const Payload &payload)
    {
        return Message{clientId, Message::Type::request, payload};
    }

    static Message createResponse(const clientId_t &clientId, const Payload &payload)
    {
        return Message{clientId, Message::Type::response, payload};
    }

    static Message createAlert(const clientId_t &clientId, const Payload &payload)
    {
        return Message{clientId, Message::Type::alert, payload};
    }
};
} // namespace toad::communication_protocol::tcp
