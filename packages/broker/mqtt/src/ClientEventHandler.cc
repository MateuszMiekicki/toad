#include "toad/broker/mqtt/ClientEventHandler.hh"

using namespace MQTT_NS::literals;
namespace toad::broker::mqtt
{
// connection handlers
void ClientEventHandler::onClose()
{
}

void ClientEventHandler::onError(errorCode_t)
{
}

bool ClientEventHandler::onConnect(buffer_t client_id,
                                   optional_t<buffer_t> const& username,
                                   optional_t<buffer_t> const& password,
                                   optional_t<will_t>,
                                   bool, // todo: use alias
                                   std::uint16_t, // todo: use alias
                                   properties_t)
{

                    std::cout << "[server] client_id    : " << client_id << std::endl;
                    std::cout << "[server] username     : " << (username ? username.value() : "none"_mb) << std::endl;
                    std::cout << "[server] password     : " << (password ? password.value() : "none"_mb) << std::endl;
}

void ClientEventHandler::onDisconnect(disconnectReasonCode_t, properties_t)
{
}

// tood: move to mqtt specific hanlder class
bool ClientEventHandler::onPuback(packet_id_t, pubackReasonCode_t, properties_t)
{
}

bool ClientEventHandler::onPubrec(packet_id_t, pubrecReasonCode_t, properties_t)
{
}

bool ClientEventHandler::onPubrel(packet_id_t, pubrelReasonCode_t, properties_t)
{
}

bool ClientEventHandler::onPubcomp(packet_id_t, pubcompReasonCode_t, properties_t)
{
}

bool ClientEventHandler::onPublish(optional_t<packet_id_t>, publishOptions_t, buffer_t, buffer_t, properties_t)
{
}

bool ClientEventHandler::onSubscribe(packet_id_t, subscribeEntries_t, properties_t)
{
}

bool ClientEventHandler::onUnsubscribe(packet_id_t, unsubscribeEntries_t, properties_t)
{
}

} // namespace toad::broker::mqtt