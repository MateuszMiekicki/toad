#pragma once
#include <mqtt/subscribe_options.hpp>

namespace toad::broker
{
using qualityOfService_t = MQTT_NS::qos;
using retainAsPublished_t = MQTT_NS::rap;
} // namespace toad::broker::mqtt
