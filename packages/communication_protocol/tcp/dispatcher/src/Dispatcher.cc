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
            case Message::Message::Type::request:
            {
                DEBUG_LOG("Request processing");
                try
                {
                    broker_.send(message);
                }
                catch(const std::exception& e)
                {
                    WARN_LOG("Exception during request processing: {}", e.what());
                    hub_.push(MessageFactory::createFailureResponse(message.getClientId(),
                                                                    PayloadFactory::createFailureDetail(e.what())));
                }
            }
            break;
            case Message::Message::Type::response:
            {
                DEBUG_LOG("Response processing");
                try
                {
                    requester_.send(message);
                }
                catch(const std::exception& e)
                {
                    WARN_LOG("Exception during response processing: {}. Send response failure", e.what());
                    requester_.send(
                        MessageFactory::createFailureResponse(message.getClientId(),
                                                              PayloadFactory::createFailureDetail(e.what())));
                }
            }
            break;
            case Message::Message::Type::report:
            {
                DEBUG_LOG("Alert processing");
                notifier_.send(message);
            }
            break;
            case Message::Message::Type::unknown:
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
