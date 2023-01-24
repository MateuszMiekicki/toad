#pragma once
#include "toad/broker/mqtt/interface/EventHandler.hh"
// #include "toad/broker/mqtt/Sessions.hh"
namespace toad::broker::mqtt
{
class EventHandler : public interface::EventHandler
{
  private:
  // Sessions sessions_;
  public:
    EventHandler(const EventHandler&) = delete;
    EventHandler& operator=(const EventHandler&) = delete;
    ~EventHandler()=default;
    EventHandler()=default;
    EventHandler(EventHandler&&);
    EventHandler& operator=(EventHandler&&);

    // todo: move to other, independent class related with server abstract
     void onAccept(std::shared_ptr<toad::network::endpoint_t>)override;
     void onError(errorCode_t)override;

    // connection handlers
     void onClose()override;
     void onClientError(errorCode_t)override;
     bool onConnect(buffer_t,
                   optional_t<buffer_t> const&,
                   optional_t<buffer_t> const&,
                   optional_t<will_t>,
                   bool, // todo: use alias
                   std::uint16_t, // todo: use alias
                   properties_t)override;
     void onDisconnect(disconnectReasonCode_t, properties_t)override;

    // tood: move to mqtt specific hanlder class
     bool onPuback(packet_id_t, pubackReasonCode_t, properties_t)override;
     bool onPubrec(packet_id_t, pubrecReasonCode_t, properties_t)override;
     bool onPubrel(packet_id_t, pubrelReasonCode_t, properties_t)override;
     bool onPubcomp(packet_id_t, pubcompReasonCode_t, properties_t)override;

     bool onPublish(optional_t<packet_id_t>,
                           publishOptions_t,
                           buffer_t,
                           buffer_t,
                           properties_t)override;
     bool onSubscribe(packet_id_t, subscribeEntries_t, properties_t)override;
     bool onUnsubscribe(packet_id_t, unsubscribeEntries_t, properties_t)override;

};
} // namespace toad::server::broker
