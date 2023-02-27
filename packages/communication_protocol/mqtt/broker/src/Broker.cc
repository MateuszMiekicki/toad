#include "toad/communication_protocol/mqtt/broker/Broker.hh"

#include "toad/communication_protocol/endpoint/Endpoint.hh"
#include "toad/communication_protocol/mqtt/broker/Connection.hh"

namespace toad::communication_protocol::mqtt
{
Broker::Broker(const Endpoint& endpoint, std::unique_ptr<interface::BrokerEventHandler> brokerEventHandler) :
    brokerEventHandler_{std::move(brokerEventHandler)}, brokerAcceptor_{}, broker_(endpoint.endpoint(), brokerAcceptor_)
{
}

bool Broker::start()
{
    broker_.listen();
    brokerAcceptor_.run();
    return true;
}

void Broker::onAccept()
{
    broker_.set_accept_handler(
        [&](Connection::con_sp_t con)
        {
        Connection connection(con);
        brokerEventHandler_->onAccept(connection);
    });
}

void Broker::onError()
{
}

} // namespace toad::communication_protocol::mqtt