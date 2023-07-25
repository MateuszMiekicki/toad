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

    static std::string serialize(const Payload::Type &type)
    {
        switch(type)
        {
            case Payload::Type::json:
                return "json";
            case Payload::Type::unknown:
            default:
                return "unknown";
        }
    }
};

struct PayloadFactory
{
    static Payload create(const std::string &);
    static Payload createJson(const std::string &);
};
} // namespace toad::communication_protocol::tcp

#include "toad/communication_protocol/tcp/message/formatter/Payload.tpp"