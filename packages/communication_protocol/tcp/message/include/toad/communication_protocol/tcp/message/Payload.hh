#pragma once
#include <string>
#include <tuple>

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

    bool operator==(const Payload &) const
    {
        return std::tie(type_, payload_) == std::tie(type_, payload_);
    }
};

struct PayloadFactory
{
    static Payload create(const std::string &);
    static Payload createJson(const std::string &);

    static Payload createFailureDetail(const std::string &cause)
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
};
} // namespace toad::communication_protocol::tcp

#include "toad/communication_protocol/tcp/message/formatter/Payload.tpp"