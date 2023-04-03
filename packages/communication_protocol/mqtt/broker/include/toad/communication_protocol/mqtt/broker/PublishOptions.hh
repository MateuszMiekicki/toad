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
};
} // namespace toad::communication_protocol::mqtt