#pragma once
#include "toad/communication_protocol/mqtt/mqtt_broker/SubscriptionOptions.hh"

#include <mqtt/buffer.hpp>

namespace toad::communication_protocol
{
using topic_t = MQTT_NS::buffer;
} // namespace toad::communication_protocol

namespace toad::communication_protocol::mqtt::mqtt_broker
{
class Topic
{
  private:
    topic_t topic_;
    qualityOfService_t qualityOfService_;
    retainAsPublished_t retainAsPublished_;

  public:
    Topic(const Topic&) = delete;
    Topic& operator=(const Topic&) = delete;

    ~Topic();
    Topic(topic_t, qualityOfService_t, retainAsPublished_t);
    Topic(Topic&&);
    Topic& operator=(Topic&&);

    bool operator<(const Topic&);

    topic_t getTopic() const;
    qualityOfService_t getQoS() const;
    retainAsPublished_t getRAP() const;
};
} // namespace toad::communication_protocol::mqtt::mqtt_broker
