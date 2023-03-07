#include "toad/communication_protocol/mqtt/broker/Broker.hh"

#include "toad/communication_protocol/endpoint/Endpoint.hh"
#include "toad/communication_protocol/mqtt/Logger.hh"
#include "toad/communication_protocol/mqtt/broker/Connection.hh"
#include "toad/communication_protocol/mqtt/broker/ErrorCode.hh"

#include <iostream>

namespace toad::communication_protocol::mqtt
{
Broker::Broker(const Endpoint& endpoint, std::unique_ptr<interface::BrokerEventHandler> brokerEventHandler) :
    brokerEventHandler_{std::move(brokerEventHandler)}, brokerAcceptor_{}, broker_(endpoint.endpoint(), brokerAcceptor_)
{
    broker_.set_protocol_version(::MQTT_NS::protocol_version::v5);
}

bool Broker::start()
{
    setHandleOnConnection();
    setHandleOnError();
    listen();
    accept();
    return true;
}

void Broker::setHandleOnConnection()
{
    broker_.set_accept_handler(
        [&](Connection::con_sp_t con)
        {
        Connection connection(con);
        brokerEventHandler_->onAccept(connection);
    });
}

void Broker::setHandleOnError()
{
    broker_.set_error_handler(
        [&](::MQTT_NS::error_code ec)
        {
        WARN_LOG("Broker handled error code: {}", ec.message());
        ErrorCode errorCode;
        brokerEventHandler_->onError(errorCode);
    });
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