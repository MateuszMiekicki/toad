#include "toad/communication_protocol/tcp/dispatcher/Dispatcher.hh"
#include "toad/communication_protocol/tcp/Logger.hh"

namespace toad::communication_protocol::tcp
{
Dispatcher::Dispatcher(Hub& hub, Broker& broker, Requester& requester) :
    hub_{hub}, broker_{broker}, requester_{requester}
{
}

void Dispatcher::start()
{
    while(true)
    {
        const auto message = hub_.pop();
        INFO_LOG("Dispatcher received message");
        INFO_LOG("Message clientId: {}", message.clientId_);
        INFO_LOG("Message payload: {}", message.payload_.payload);
        switch(message.type_)
        {
            case Message::Type::request:
            {
                DEBUG_LOG("Request processing");
                broker_.send(message);
            }
            break;
            case Message::Type::response:
            {
                DEBUG_LOG("Response processing");
                requester_.send(message);
            }
            break;
            case Message::Type::alert:
            {
                DEBUG_LOG("Alert processing");
                // push alert
            }
            break;
            case Message::Type::unknown:
            {
                WARN_LOG("Unknown message type");
            }
            break;
            default:
            {
                WARN_LOG("Not implemented message type");
            }
            break;
        }
    }
}
} // namespace toad::communication_protocol::tcp
