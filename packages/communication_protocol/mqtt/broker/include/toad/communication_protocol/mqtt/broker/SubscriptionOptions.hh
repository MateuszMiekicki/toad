#pragma once
#include <cstdint>

namespace toad::communication_protocol::mqtt
{
enum class QualityOfService : std::uint8_t
{
    atMostOnce,
    atLeastOnce,
    exactlyOnce
};
enum class RetainAsPublished : std::uint8_t
{
    discard,
    retain
};

struct SubscriptionOptions
{
    QualityOfService qualityOfService;
    RetainAsPublished retainAsPublished;
};
} // namespace toad::communication_protocol::mqtt