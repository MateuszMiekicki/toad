#include "toad/communication_protocol/mqtt/broker/SubscriptionManager.hh"

#include "toad/communication_protocol/mqtt/broker/PublishOptions.hh"

namespace
{
::MQTT_NS::qos convert(toad::communication_protocol::mqtt::QualityOfService qos)
{
    using namespace toad::communication_protocol::mqtt;
    switch(qos)
    {
        case QualityOfService::atMostOnce:
            return ::MQTT_NS::qos::at_most_once;
        case QualityOfService::atLeastOnce:
            return ::MQTT_NS::qos::at_least_once;
        case QualityOfService::exactlyOnce:
            return ::MQTT_NS::qos::exactly_once;
        default:
            throw std::exception();
    }
}

::MQTT_NS::qos
getPreferredValueOfQualityOfService(const toad::communication_protocol::mqtt::Subscription& subscription,
                                    const toad::communication_protocol::mqtt::PublishOptions& publishOptions)
{
    return std::min(convert(subscription.subscriptionOptions_.qualityOfService),
                    convert(publishOptions.qualityOfService));
}
} // namespace

namespace toad::communication_protocol::mqtt
{
void SubscriptionManager::publish(topic_t topic_name, topic_t contents, const PublishOptions& publishOptions)
{
    auto const& idx = subscriptions_.get<tag_topic>();
    auto r = idx.equal_range(topic_name);
    for(; r.first != r.second; ++r.first)
    {
        r.first->connection_->get()->publish(0,
                                             std::string(topic_name.data(), topic_name.size()),
                                             std::string(contents.data(), contents.size()),
                                             getPreferredValueOfQualityOfService(*(r.first), publishOptions));
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