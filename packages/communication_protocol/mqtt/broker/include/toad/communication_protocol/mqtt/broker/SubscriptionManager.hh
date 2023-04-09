#pragma once
#include "toad/communication_protocol/mqtt/broker/Subscription.hh"

namespace toad::communication_protocol::mqtt
{
struct PublishOptions;

class SubscriptionManager
{
  private:
    subscriptions_t subscriptions_{};
    auto isSubscriberToTopic(const Subscription&) const;

  public:
    void publish(topic_t, content_t, const PublishOptions&);
    void subscribe(const Subscription&);
    void unsubscribe(const Subscription&);
    std::size_t getNumberActiveSubscribers() const;
};
} // namespace toad::communication_protocol::mqtt