#pragma once
#include "toad/communication_protocol/tcp/message/Identifier.hh"
#include "toad/communication_protocol/tcp/message/Payload.hh"
#include <cstdint>
#include <string>

namespace toad::communication_protocol::tcp
{
struct Message
{
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
    using clientId_t = std::string;
    const MessageId id_;
    const clientId_t clientId_;

    const Type type_;

    const Purpose purpose_;
    const Payload payload_;

    Message(const clientId_t &clientId, const Type &type, const Purpose &purpose, const Payload &payload) :
        id_{}, clientId_{clientId}, type_{type}, purpose_{purpose}, payload_{payload}
    {
    }

    uuid getId() const
    {
        return id_.id;
    }

    clientId_t getClientId() const
    {
        return clientId_;
    }

    Payload::buffer_t getRawPayload() const
    {
        return payload_.getPayload();
    }

    Payload getPayload() const
    {
        return payload_;
    }

    Type getType() const
    {
        return type_;
    }

    Purpose getPurpose() const
    {
        return purpose_;
    }

    static Type deserializeType(const std::string &type)
    {
        if(type == "request")
        {
            return Type::request;
        }
        else if(type == "response")
        {
            return Type::response;
        }
        else if(type == "report")
        {
            return Type::report;
        }
        else if(type == "required")
        {
            return Type::required;
        }
        else if(type == "confirm")
        {
            return Type::confirm;
        }
        return Type::unknown;
    }

    static Purpose deserializePurpose(const std::string &purpose)
    {
        if(purpose == "failure")
        {
            return Purpose::failure;
        }
        else if(purpose == "set_configuration")
        {
            return Purpose::setConfiguration;
        }
        else if(purpose == "get_configuration")
        {
            return Purpose::getConfiguration;
        }
        else if(purpose == "alert")
        {
            return Purpose::alert;
        }
        else if(purpose == "ping")
        {
            return Purpose::ping;
        }
        else if(purpose == "pong")
        {
            return Purpose::pong;
        }
        return Purpose::unknown;
    }
};

class MessageFactory
{
  public:
    static Message createAlertReport(const Message::clientId_t &clientId, const Payload &payload)
    {
        return Message{clientId, Message::Type::report, Message::Purpose::alert, payload};
    }

    static Message createGetConfigurationRequest(const Message::clientId_t &clientId, const Payload &payload)
    {
        return Message{clientId, Message::Type::request, Message::Purpose::getConfiguration, payload};
    }

    static Message createGetConfigurationResponse(const Message::clientId_t &clientId, const Payload &payload)
    {
        return Message{clientId, Message::Type::response, Message::Purpose::getConfiguration, payload};
    }

    static Message createFailureResponse(const Message::clientId_t &clientId, const Payload &payload)
    {
        return Message{clientId, Message::Type::response, Message::Purpose::failure, payload};
    }
};
} // namespace toad::communication_protocol::tcp

#include "toad/communication_protocol/tcp/message/formatter/Message.tpp"