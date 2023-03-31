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
} // namespace toad::communication_protocol::mqtt

#include "toad/communication_protocol/mqtt/broker/formatter/QualityOfService.tpp"