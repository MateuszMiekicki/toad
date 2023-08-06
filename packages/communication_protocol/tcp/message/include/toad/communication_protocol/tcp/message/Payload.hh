#pragma once
#include <string>

namespace toad::communication_protocol::tcp
{
class Payload
{
  public:
    using buffer_t = std::string;
    enum class Type
    {
        unknown,
        json,
    };

  private:
    const Type type_;
    const buffer_t payload_;

  public:
    Payload(const buffer_t &, const Type &);

    Type getType() const;
    buffer_t getPayload() const;

    bool operator==(const Payload &) const;
    bool operator!=(const Payload &) const;
};

struct PayloadFactory
{
    static Payload create(const Payload::buffer_t &);
    static Payload createJson(const Payload::buffer_t &);
    static Payload createFailureDetail(const Payload::buffer_t &);
};
} // namespace toad::communication_protocol::tcp

#include "toad/communication_protocol/tcp/message/formatter/Payload.tpp"