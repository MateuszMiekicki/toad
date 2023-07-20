#include "toad/communication_protocol/tcp/message/Payload.hh"

namespace toad::communication_protocol::tcp
{
Payload::Payload(const Payload::buffer_t &payload, const Type &type) : type_{type}, payload_{payload}
{
}

Payload::Type Payload::getType() const
{
    return type_;
}

Payload::buffer_t Payload::getPayload() const
{
    return payload_;
}

Payload PayloadFactory::create(const Payload::buffer_t &payload)
{
    return Payload{payload, Payload::Type::unknown};
}

Payload PayloadFactory::createJson(const Payload::buffer_t &payload)
{
    return Payload{payload, Payload::Type::json};
}
} // namespace toad::communication_protocol::tcp