#include "toad/broker/mqtt/interface/BrokerEventHandler.hh"

#include "toad/broker/mqtt/BrokerEventHandler.hh"
#include "toad/broker/mqtt/Sessions.hh"
#include "toad/broker/mqtt/Session.hh"
#include <iostream>
using con_t = MQTT_NS::server<>::endpoint_t;
using con_sp_t = std::shared_ptr<con_t>;
namespace toad::broker::mqtt
{
// todo: move to other, independent class related with server abstract
void BrokerEventHandler::onAccept(con_sp_t connection)
{
    std::cout<<"accept\n";
    // Session session(connection);
    Session s;
    s.session_ = connection;
    sessions_.addSession(s);
}

void BrokerEventHandler::onError(errorCode_t ec)
{
    std::cout << "error: " << ec.message() << std::endl;
}
} // namespace toad::broker::mqtt
