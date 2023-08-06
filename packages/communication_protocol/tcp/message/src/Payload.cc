#include "toad/communication_protocol/tcp/message/Payload.hh"
#include <tuple>

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

bool Payload::operator==(const Payload &) const
{
    return std::tie(type_, payload_) == std::tie(type_, payload_);
}

bool Payload::operator!=(const Payload &rhs) const
{
    return !(rhs == *this);
}

Payload PayloadFactory::create(const Payload::buffer_t &payload)
{
    return Payload{payload, Payload::Type::unknown};
}

Payload PayloadFactory::createJson(const Payload::buffer_t &payload)
{
    return Payload{payload, Payload::Type::json};
}

Payload PayloadFactory::createFailureDetail(const Payload::buffer_t &cause)
{
    const auto detail = R"(
    {
        "cause": {
            "detail": ")" +
                        cause + R"("
        }
    }
)";
    return PayloadFactory::createJson(detail);
}
} // namespace toad::communication_protocol::tcp