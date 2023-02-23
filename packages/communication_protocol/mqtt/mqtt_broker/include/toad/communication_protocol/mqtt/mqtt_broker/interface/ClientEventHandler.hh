#pragma once
#include "toad/network/endpoint/Endpoint.hh"

#include <mqtt_server_cpp.hpp>

using buffer_t = MQTT_NS::buffer;
using errorCode_t = MQTT_NS::error_code;
template<typename T>
using optional_t = MQTT_NS::optional<T>;
using will_t = MQTT_NS::will;
using properties_t = MQTT_NS::v5::properties;
using disconnectReasonCode_t = MQTT_NS::v5::disconnect_reason_code;
using publishOptions_t = MQTT_NS::publish_options;

using pubackReasonCode_t = MQTT_NS::v5::puback_reason_code;
using pubrecReasonCode_t = MQTT_NS::v5::pubrec_reason_code;
using pubrelReasonCode_t = MQTT_NS::v5::pubrel_reason_code;
using pubcompReasonCode_t = MQTT_NS::v5::pubcomp_reason_code;

using subscribeEntries_t = std::vector<MQTT_NS::subscribe_entry>;
using unsubscribeEntries_t = std::vector<MQTT_NS::unsubscribe_entry>;

using con_t = MQTT_NS::server<>::endpoint_t;
using con_sp_t = std::shared_ptr<con_t>;
using packet_id_t = typename std::remove_reference_t<con_t>::packet_id_t;
using endpointServer_t = MQTT_NS::server<>::endpoint_t;

namespace toad::communication_protocol::mqtt::mqtt_broker::interface
{
class ClientEventHandler
{
  public:
    virtual ~ClientEventHandler() = default;

    // connection handlers
    virtual void onClose() = 0;
    virtual void onError(errorCode_t) = 0;
    virtual bool onConnect(buffer_t,
                           optional_t<buffer_t> const&,
                           optional_t<buffer_t> const&,
                           optional_t<will_t>,
                           bool, // todo: use alias
                           std::uint16_t, // todo: use alias
                           properties_t) = 0;
    virtual void onDisconnect(disconnectReasonCode_t, properties_t) = 0;

    // tood: move to mqtt specific hanlder class
    virtual bool onPuback(packet_id_t, pubackReasonCode_t, properties_t) = 0;
    virtual bool onPubrec(packet_id_t, pubrecReasonCode_t, properties_t) = 0;
    virtual bool onPubrel(packet_id_t, pubrelReasonCode_t, properties_t) = 0;
    virtual bool onPubcomp(packet_id_t, pubcompReasonCode_t, properties_t) = 0;

    virtual bool onPublish(optional_t<packet_id_t>, publishOptions_t, buffer_t, buffer_t, properties_t) = 0;
    virtual bool onSubscribe(packet_id_t, subscribeEntries_t, properties_t) = 0;
    virtual bool onUnsubscribe(packet_id_t, unsubscribeEntries_t, properties_t) = 0;
};
} // namespace toad::communication_protocol::mqtt::mqtt_broker::interface