#pragma once
#include "toad/communication_protocol/mqtt/broker/QualityOfService.hh"
#include "toad/communication_protocol/mqtt/broker/RetainAsPublished.hh"
#include <cstdint>

namespace toad::communication_protocol::mqtt
{
enum class Duplicate : std::uint8_t
{
    no,
    yes
};

struct PublishOptions
{
    QualityOfService qualityOfService;
    RetainAsPublished retainAsPublished;
    Duplicate duplicate;

    friend bool operator==(const PublishOptions& lhs, const PublishOptions& rhs)
    {
        return std::tie(lhs.qualityOfService, lhs.retainAsPublished, lhs.duplicate) ==
               std::tie(rhs.qualityOfService, rhs.retainAsPublished, rhs.duplicate);
    }
};
} // namespace toad::communication_protocol::mqtt