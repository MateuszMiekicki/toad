#include "toad/communication_protocol/mqtt/broker/Broker.hh"
#include "toad/communication_protocol/endpoint/Endpoint.hh"
#include "toad/communication_protocol/mqtt/broker/Connection.hh"
#include "toad/communication_protocol/mqtt/broker/ErrorCode.hh"
#include "toad/communication_protocol/mqtt/Logger.hh"

namespace toad::communication_protocol::tcp
{
Broker::Broker(const Endpoint& endpoint, std::unique_ptr<interface::BrokerEventHandler> brokerEventHandler) :
    brokerEventHandler_{std::move(brokerEventHandler)}, brokerAcceptor_{}, broker_(endpoint.endpoint(), brokerAcceptor_)
{
    INFO_LOG("MQTT broker: {{\"mqtt_broker:\": {{\"version\": \"3.1.1\", {}}}}}", endpoint);
    broker_.set_protocol_version(::MQTT_NS::protocol_version::v3_1_1);
}

bool Broker::start()
{
    setupHandleOnConnection();
    setupHandleOnError();
    INFO_LOG("MQTT broker: start lisen and accept connection");
    listen();
    accept();
    return true;
}

void Broker::setupHandleOnConnection()
{
    broker_.set_accept_handler(
        [&](Connection::con_sp_t con)
        {
        auto connection = std::make_shared<Connection>(std::move(con));
        brokerEventHandler_->onAccept(connection);
    });
}

void Broker::setupHandleOnError()
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
} // namespace toad::communication_protocol::tcp