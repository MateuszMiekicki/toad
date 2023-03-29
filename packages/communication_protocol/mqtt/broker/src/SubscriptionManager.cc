#include "toad/communication_protocol/mqtt/broker/SubscriptionManager.hh"

namespace toad::communication_protocol::mqtt
{
void SubscriptionManager::publish(topic_t topic_name, topic_t contents, const SubscriptionOptions&)
{
    auto const& idx = subscriptions_.get<tag_topic>();
                    auto r = idx.equal_range(topic_name);
                    for (; r.first != r.second; ++r.first) {
                        r.first->connection_->get()->publish(0,
                            std::string(topic_name.data(), topic_name.size()),
                            std::string(contents.data(), contents.size()),
                            {}
                        );
                    }
}

void SubscriptionManager::subscribe(const Subscription& subscription)
{
    subscriptions_.emplace(std::move(subscription));
}

void SubscriptionManager::unsubscribe(const Subscription&)
{
}
} // namespace toad::communication_protocol::mqtt