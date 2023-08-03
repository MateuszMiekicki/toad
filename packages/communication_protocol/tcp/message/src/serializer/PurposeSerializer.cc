#include "toad/communication_protocol/tcp/message/serializer/PurposeSerializer.hh"
#include "toad/communication_protocol/tcp/message/Message.hh"

namespace toad::communication_protocol::tcp
{
std::string serialize(Message::Purpose purpose)
{
    switch(purpose)
    {
        case Message::Purpose::failure:
            return "failure";
        case Message::Purpose::getConfiguration:
            return "get_configuration";
        case Message::Purpose::setConfiguration:
            return "set_configuration";
        case Message::Purpose::alert:
            return "alert";
        case Message::Purpose::ping:
            return "ping";
        case Message::Purpose::pong:
            return "pong";
        case Message::Purpose::setSensorsConfiguration:
            return "set_sensors_configuration";
        case Message::Purpose::unknown:
        default:
            return "unknown";
    }
}
} // namespace toad::communication_protocol::tcp
