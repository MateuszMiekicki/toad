#include "toad/communication_protocol/mqtt/broker/SubscriptionManager.hh"
#include "toad/communication_protocol/mqtt/broker/PublishOptions.hh"
#include "toad/communication_protocol/mqtt/Logger.hh"
#include <unordered_set>

namespace
{
toad::communication_protocol::mqtt::QualityOfService
getPreferredValueOfQualityOfService(const toad::communication_protocol::mqtt::SubscriptionOptions& subscriptionOptions,
                                    const toad::communication_protocol::mqtt::PublishOptions& publishOptions)
{
    return std::min(subscriptionOptions.qualityOfService, publishOptions.qualityOfService);
}

toad::communication_protocol::mqtt::PublishOptions
buildLowImpactPublishOptions(toad::communication_protocol::mqtt::QualityOfService qos)
{
    using namespace toad::communication_protocol::mqtt;
    return {qos, RetainAsPublished::discard, Duplicate::no};
}

template<typename It>
struct Range
{
    It begin_;
    It end_;

    It begin() const
    {
        return begin_;
    }

    It end() const
    {
        return end_;
    }
};

template<typename It>
Range<It> toRange(const std::pair<It, It>& p)
{
    return {p.first, p.second};
}

auto findAllSubscribersTopic(const toad::communication_protocol::mqtt::subscriptions_t& subscriptions,
                             const toad::communication_protocol::mqtt::topic_t& topic_name)
{
    auto const& idx = subscriptions.get<toad::communication_protocol::mqtt::tag_topic>();
    return toRange(idx.equal_range(topic_name));
}
} // namespace

namespace toad::communication_protocol::mqtt
{
void SubscriptionManager::publish(topic_t topicName, content_t content, const PublishOptions& publishOptions)
{
    for(const auto& [subscriber, _, subscriptionOptions]: findAllSubscribersTopic(subscriptions_, topicName))
    {
        subscriber->publish(
            topicName,
            content,
            buildLowImpactPublishOptions(getPreferredValueOfQualityOfService(subscriptionOptions, publishOptions)));
    }
}

void SubscriptionManager::subscribe(Subscription subscription)
{
    subscriptions_.emplace(std::move(subscription));
}

auto SubscriptionManager::isSubscriberToTopic(const Subscription& subscription) const
{
    return subscriptions_.find(std::make_tuple(subscription.subscriber_, subscription.topic_));
}

void SubscriptionManager::unsubscribe(const Subscription& subscription)
{
    if(auto it = isSubscriberToTopic(subscription); it != subscriptions_.end())
    {
        subscriptions_.erase(it);
    }
}

std::size_t SubscriptionManager::getNumberActiveSubscribers() const
{
    std::unordered_set<subscriber_t> unique_subscribers;
    for(const auto& subscription: subscriptions_.get<tag_con>())
    {
        unique_subscribers.insert(subscription.subscriber_);
    }
    return unique_subscribers.size();
}
} // namespace toad::communication_protocol::mqtt