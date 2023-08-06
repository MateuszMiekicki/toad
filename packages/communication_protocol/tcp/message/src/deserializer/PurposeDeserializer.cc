#include "toad/communication_protocol/tcp/message/deserializer/PurposeDeserializer.hh"
#include <boost/algorithm/string/predicate.hpp>

namespace toad::communication_protocol::tcp
{
Message::Purpose deserializeMessagePurpose(const std::string &purpose)
{
    if(boost::iequals(purpose, "failure"))
    {
        return Message::Purpose::failure;
    }
    else if(boost::iequals(purpose, "set_configuration"))
    {
        return Message::Purpose::setConfiguration;
    }
    else if(boost::iequals(purpose, "get_configuration"))
    {
        return Message::Purpose::getConfiguration;
    }
    else if(boost::iequals(purpose, "alert"))
    {
        return Message::Purpose::alert;
    }
    else if(boost::iequals(purpose, "ping"))
    {
        return Message::Purpose::ping;
    }
    else if(boost::iequals(purpose, "pong"))
    {
        return Message::Purpose::pong;
    }
    return Message::Purpose::unknown;
}
} // namespace toad::communication_protocol::tcp