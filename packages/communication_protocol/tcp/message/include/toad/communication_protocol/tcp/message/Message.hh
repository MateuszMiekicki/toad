#pragma once
#include "toad/communication_protocol/tcp/message/Identifier.hh"
#include "toad/communication_protocol/tcp/message/Payload.hh"
#include <cstdint>
#include <string>
#include <tuple>

namespace toad::communication_protocol::tcp
{
class Message
{
  public:
    using clientId_t = std::string;
    enum class Purpose : std::uint8_t
    {
        unknown,
        failure,
        getConfiguration,
        setConfiguration,
        setSensorsConfiguration,
        alert,
        alertIndication,
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

    bool operator==(const Message &) const;
    bool operator!=(const Message &) const;
};

struct MessageFactory
{
    static Message createAlertReport(const Message::clientId_t &, const Payload &);
    static Message createAlertIndicationReport(const Message::clientId_t &, const Payload &);
    static Message createGetConfigurationRequest(const Message::clientId_t &, const Payload &);
    static Message createGetConfigurationResponse(const Message::clientId_t &, const Payload &);
    static Message createFailureResponse(const Message::clientId_t &, const Payload &);
};
} // namespace toad::communication_protocol::tcp

#include "toad/communication_protocol/tcp/message/formatter/Message.tpp"