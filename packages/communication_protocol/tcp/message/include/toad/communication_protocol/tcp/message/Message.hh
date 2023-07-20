#pragma once
#include "toad/communication_protocol/tcp/message/Identifier.hh"
#include "toad/communication_protocol/tcp/message/Payload.hh"

namespace toad::communication_protocol::tcp
{
struct Message
{
    using clientId_t = std::string;
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

    uuid getId() const
    {
        return id_.id;
    }
};

class MessageFactory
{
  public:
    static Message createRequest(const Message::clientId_t &clientId, const Payload &payload)
    {
        return Message{clientId, Message::Type::request, payload};
    }

    static Message createResponse(const Message::clientId_t &clientId, const Payload &payload)
    {
        return Message{clientId, Message::Type::response, payload};
    }

    static Message createAlert(const Message::clientId_t &clientId, const Payload &payload)
    {
        return Message{clientId, Message::Type::alert, payload};
    }
};
} // namespace toad::communication_protocol::tcp
