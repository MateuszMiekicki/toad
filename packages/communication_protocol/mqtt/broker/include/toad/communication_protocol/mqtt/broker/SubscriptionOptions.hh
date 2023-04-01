#pragma once
#include "toad/communication_protocol/mqtt/broker/QualityOfService.hh"
#include "toad/communication_protocol/mqtt/broker/RetainAsPublished.hh"

namespace toad::communication_protocol::mqtt
{
struct SubscriptionOptions
{
    QualityOfService qualityOfService;
    RetainAsPublished retainAsPublished;
};
} // namespace toad::communication_protocol::mqtt