#include "toad/communication_protocol/mqtt/broker/Broker.hh"

#include "toad/communication_protocol/endpoint/Endpoint.hh"
#include "toad/communication_protocol/mqtt/Logger.hh"
#include "toad/communication_protocol/mqtt/broker/Connection.hh"

#include <iostream>

namespace toad::communication_protocol::mqtt
{
Broker::Broker(const Endpoint& endpoint, std::unique_ptr<interface::BrokerEventHandler> brokerEventHandler) :
    brokerEventHandler_{std::move(brokerEventHandler)}, brokerAcceptor_{}, broker_(endpoint.endpoint(), brokerAcceptor_)
{
}

bool Broker::start()
{
    prepareAcceptHandler();
    listen();
    accept();
    return true;
}

void Broker::prepareAcceptHandler()
{
    std::cout << "Broker::onAccept\n";

    broker_.set_accept_handler(
        [&](Connection::con_sp_t con)
        {
        std::cout << "cnew onnection\n";

        INFO_LOG("new connection");
        Connection connection(con);
        brokerEventHandler_->onAccept(connection);
    });
}

void Broker::onError()
{
}

void Broker::listen()
{
    broker_.listen();
}

void Broker::accept()
{
    brokerAcceptor_.run();
}
} // namespace toad::communication_protocol::mqtt