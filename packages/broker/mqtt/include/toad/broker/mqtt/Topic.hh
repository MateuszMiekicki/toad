#pragma once
#include "toad/broker/mqtt/SubscriptionOptions.hh"
#include <mqtt/buffer.hpp>

namespace toad::broker
{
using topic_t = MQTT_NS::buffer;
}
namespace toad::broker::mqtt
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
} // namespace toad::broker::mqtt
