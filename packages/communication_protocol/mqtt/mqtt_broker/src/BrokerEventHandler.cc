#include "toad/communication_protocol/mqtt/mqtt_broker/interface/BrokerEventHandler.hh"

#include "toad/communication_protocol/mqtt/mqtt_broker/BrokerEventHandler.hh"
#include "toad/communication_protocol/mqtt/mqtt_broker/Session.hh"
#include "toad/communication_protocol/mqtt/mqtt_broker/Sessions.hh"

#include <iostream>
using con_t = MQTT_NS::server<>::endpoint_t;
using con_sp_t = std::shared_ptr<con_t>;

namespace toad::communication_protocol::mqtt::mqtt_broker
{
BrokerEventHandler::BrokerEventHandler(std::unique_ptr<interface::ClientEventHandler> clientEventHandler) :
    clientEventHandler_{std::move(clientEventHandler)}
{
}

// todo: move to other, independent class related with server abstract
void BrokerEventHandler::onAccept(con_sp_t connection)
{
    std::cout << "accept\n";
    auto& ep = *connection;
    std::weak_ptr<con_t> wp(connection);

    ep.start_session(std::move(connection));
    ep.set_v5_connect_handler(std::bind(&interface::ClientEventHandler::onConnect,
                                        clientEventHandler_.get(),
                                        std::placeholders::_1,
                                        std::placeholders::_2,
                                        std::placeholders::_3,
                                        std::placeholders::_4,
                                        std::placeholders::_5,
                                        std::placeholders::_6,
                                        std::placeholders::_7));
    Session s;
    s.session_ = connection;
    sessions_.addSession(s);
    std::exit(0);
}

void BrokerEventHandler::onError(errorCode_t ec)
{
    std::cout << "error: " << ec.message() << std::endl;
}
} // namespace toad::communication_protocol::mqtt::mqtt_broker
