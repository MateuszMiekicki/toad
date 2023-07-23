#include "toad/communication_protocol/tcp/dispatcher/Dispatcher.hh"
#include "toad/communication_protocol/tcp/Logger.hh"

namespace toad::communication_protocol::tcp
{
Dispatcher::Dispatcher(Hub& hub, Broker& broker, Requester& requester, Notifier& notifier) :
    hub_{hub}, broker_{broker}, requester_{requester}, notifier_{notifier}
{
}

void Dispatcher::start()
{
    while(true)
    {
        const auto message = hub_.pop();
        INFO_LOG("Dispatch message: {}", message.getId());
        DEBUG_LOG("Message clientId: {}", message.clientId_);
        TRACE_LOG("Message payload: {}", message.payload_.getPayload());
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
                notifier_.send(message);
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
