#include "toad/communication_protocol/tcp/message/deserializer/TypDeserializer.hh"
#include <boost/algorithm/string/predicate.hpp>

namespace toad::communication_protocol::tcp
{
Message::Type deserializeMessageType(const std::string &type)
{
    if(boost::iequals(type, "request"))
    {
        return Message::Type::request;
    }
    else if(boost::iequals(type, "response"))
    {
        return Message::Type::response;
    }
    else if(boost::iequals(type, "report"))
    {
        return Message::Type::report;
    }
    else if(boost::iequals(type, "required"))
    {
        return Message::Type::required;
    }
    else if(boost::iequals(type, "confirm"))
    {
        return Message::Type::confirm;
    }
    return Message::Type::unknown;
}

} // namespace toad::communication_protocol::tcp