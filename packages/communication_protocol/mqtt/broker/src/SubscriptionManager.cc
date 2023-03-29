#include "toad/communication_protocol/mqtt/broker/SubscriptionManager.hh"

namespace toad::communication_protocol::mqtt
{
void SubscriptionManager::publish(const topic_t&, const SubscriptionOptions&)
{
}

void SubscriptionManager::subscribe(const Subscription& subscription)
{
    subscriptions_.emplace(std::move(subscription));
}

void SubscriptionManager::unsubscribe(const Subscription&)
{
}
} // namespace toad::communication_protocol::mqtt