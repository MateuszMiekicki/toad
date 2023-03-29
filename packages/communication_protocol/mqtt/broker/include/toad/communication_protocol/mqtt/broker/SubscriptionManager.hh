#pragma once
#include "toad/communication_protocol/mqtt/broker/Subscription.hh"

namespace toad::communication_protocol::mqtt
{
class SubscriptionManager
{
  private:
    subscriptions_t subscriptions_;

  public:
    void publish( topic_t,  topic_t, const SubscriptionOptions&);
    void subscribe(const Subscription&);
    void unsubscribe(const Subscription&);
};
} // namespace toad::communication_protocol::mqtt