#include "toad/communication_protocol/mqtt/mqtt_broker/Topic.hh"

namespace toad::communication_protocol::mqtt::mqtt_broker
{
Topic::~Topic()
{
}

Topic::Topic(topic_t topic, qualityOfService_t qualityOfService, retainAsPublished_t retainAsPublished) :
    topic_{std::move(topic)}, qualityOfService_{qualityOfService}, retainAsPublished_{retainAsPublished}
{
}

Topic::Topic(Topic&& topic) :
    topic_{std::move(topic.topic_)}, qualityOfService_{std::move(topic.qualityOfService_)},
    retainAsPublished_{std::move(topic.retainAsPublished_)}

{
}

Topic& Topic::operator=(Topic&&)
{
    // topic_ = std::move(topic.topic_);
    // qualityOfService_ = std::move(topic.qualityOfService_);
    // retainAsPublished_ = std::move(topic.retainAsPublished_);

    return *this;
}

bool Topic::operator<(const Topic&)
{
    // return std::tie(topic_, qualityOfService_, retainAsPublished_) <
    // std::tie(other.topic_, other.qualityOfService_, other.retainAsPublished_);
    return false;
}

topic_t Topic::getTopic() const
{
    return topic_;
}

qualityOfService_t Topic::getQoS() const
{
    return qualityOfService_;
}

retainAsPublished_t Topic::getRAP() const
{
    return retainAsPublished_;
}
} // namespace toad::communication_protocol::mqtt::mqtt_broker
