#include "toad/communication_protocol/tcp/message/serializer/TypeSerializer.hh"
#include "toad/communication_protocol/tcp/message/Message.hh"

namespace toad::communication_protocol::tcp
{
std::string serialize(Message::Type type)
{
    switch(type)
    {
        case Message::Type::request:
            return "request";
        case Message::Type::response:
            return "response";
        case Message::Type::report:
            return "report";
        case Message::Type::required:
            return "required";
        case Message::Type::confirm:
            return "confirm";
        case Message::Type::unknown:
        default:
            return "unknown";
    }
}
} // namespace toad::communication_protocol::tcp
