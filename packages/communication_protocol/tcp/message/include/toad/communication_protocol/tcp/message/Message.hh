#pragma once
#include "toad/communication_protocol/tcp/message/Identifier.hh"
#include "toad/communication_protocol/tcp/message/Payload.hh"
#include <cstdint>
#include <string>

namespace toad::communication_protocol::tcp
{
struct Message
{
    using clientId_t = std::string;
    const MessageId id_;
    const clientId_t clientId_;
    enum class Type : std::uint8_t
    {
        unknown,
        request,
        response,
        report
    };
    const Type type_;
    enum class Purpose : std::uint8_t
    {
        unknown,
        failure,
        configuration,
        alert
    };
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
        else
        {
            return Type::unknown;
        }
    }

    static Purpose deserializePurpose(const std::string &purpose)
    {
        if(purpose == "failure")
        {
            return Purpose::failure;
        }
        else if(purpose == "configuration")
        {
            return Purpose::configuration;
        }
        else if(purpose == "alert")
        {
            return Purpose::alert;
        }
        else
        {
            return Purpose::unknown;
        }
    }

    static std::string serialize(const Type &type)
    {
        switch(type)
        {
            case Type::request:
                return "request";
            case Type::response:
                return "response";
            case Type::report:
                return "report";
            case Type::unknown:
            default:
                return "unknown";
        }
    }

    static std::string serialize(const Purpose &purpose)
    {
        switch(purpose)
        {
            case Purpose::failure:
                return "failure";
            case Purpose::configuration:
                return "configuration";
            case Purpose::alert:
                return "alert";
            case Purpose::unknown:
            default:
                return "unknown";
        }
    }
};

class MessageFactory
{
  public:
    static Message createAlertReport(const Message::clientId_t &clientId, const Payload &payload)
    {
        return Message{clientId, Message::Type::report, Message::Purpose::alert, payload};
    }

    static Message createConfigurationRequest(const Message::clientId_t &clientId, const Payload &payload)
    {
        return Message{clientId, Message::Type::request, Message::Purpose::configuration, payload};
    }

    static Message createConfigurationResponse(const Message::clientId_t &clientId, const Payload &payload)
    {
        return Message{clientId, Message::Type::response, Message::Purpose::configuration, payload};
    }
};
} // namespace toad::communication_protocol::tcp

#include "toad/communication_protocol/tcp/message/formatter/Message.tpp"