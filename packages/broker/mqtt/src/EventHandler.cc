#include "toad/broker/mqtt/interface/EventHandler.hh"

#include "toad/broker/mqtt/EventHandler.hh"
#include "toad/broker/mqtt/Sessions.hh"

namespace toad::broker::mqtt
{
EventHandler::EventHandler(EventHandler&&)
{
}

EventHandler& EventHandler::operator=(EventHandler&&)
{
}

// todo: move to other, independent class related with server abstract
void EventHandler::onAccept(std::shared_ptr<toad::network::endpoint_t>)
{
}

void EventHandler::onError(errorCode_t)
{
}

// connection handlers
void EventHandler::onClose()
{
}

void EventHandler::onClientError(errorCode_t)
{
}

bool EventHandler::onConnect(buffer_t,
                             optional_t<buffer_t> const&,
                             optional_t<buffer_t> const&,
                             optional_t<will_t>,
                             bool, // todo: use alias
                             std::uint16_t, // todo: use alias
                             properties_t)
{
}

void EventHandler::onDisconnect(disconnectReasonCode_t, properties_t)
{
}

// tood: move to mqtt specific hanlder class
bool EventHandler::onPuback(packet_id_t, pubackReasonCode_t, properties_t)
{
}

bool EventHandler::onPubrec(packet_id_t, pubrecReasonCode_t, properties_t)
{
}

bool EventHandler::onPubrel(packet_id_t, pubrelReasonCode_t, properties_t)
{
}

bool EventHandler::onPubcomp(packet_id_t, pubcompReasonCode_t, properties_t)
{
}

bool EventHandler::onPublish(optional_t<packet_id_t>, publishOptions_t, buffer_t, buffer_t, properties_t)
{
}

bool EventHandler::onSubscribe(packet_id_t, subscribeEntries_t, properties_t)
{
}

bool EventHandler::onUnsubscribe(packet_id_t, unsubscribeEntries_t, properties_t)
{
}

} // namespace toad::broker::mqtt
