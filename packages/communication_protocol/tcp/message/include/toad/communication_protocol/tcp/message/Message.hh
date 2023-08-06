#pragma once
#include "toad/communication_protocol/tcp/message/Identifier.hh"
#include "toad/communication_protocol/tcp/message/Payload.hh"
#include <cstdint>
#include <string>
#include <tuple>

namespace toad::communication_protocol::tcp
{
struct Message
{
    using clientId_t = std::string;
    enum class Purpose : std::uint8_t
    {
        unknown,
        failure,
        getConfiguration,
        setConfiguration,
        setSensorsConfiguration,
        alert,
        ping,
        pong
    };
    enum class Type : std::uint8_t
    {
        unknown,
        request,
        response,
        report,
        required,
        confirm
    };

  private:
    const MessageId id_;
    const clientId_t clientId_;
    const Type type_;
    const Purpose purpose_;
    const Payload payload_;

  public:
    Message(const clientId_t &, const Type &, const Purpose &, const Payload &);

    uuid getId() const;

    clientId_t getClientId() const;

    Payload::buffer_t getRawPayload() const;

    Payload getPayload() const;

    Type getType() const;

    Purpose getPurpose() const;

    static Type deserializeType(const std::string &);

    static Purpose deserializePurpose(const std::string &);

    bool operator==(const Message &) const;
    bool operator!=(const Message &) const;
};

class MessageFactory
{
  public:
    static Message createAlertReport(const Message::clientId_t &clientId, const Payload &payload);
    static Message createGetConfigurationRequest(const Message::clientId_t &clientId, const Payload &payload);
    static Message createGetConfigurationResponse(const Message::clientId_t &clientId, const Payload &payload);
    static Message createFailureResponse(const Message::clientId_t &clientId, const Payload &payload);
};
} // namespace toad::communication_protocol::tcp

#include "toad/communication_protocol/tcp/message/formatter/Message.tpp"