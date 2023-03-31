#pragma once
#include <cstdint>

namespace toad::communication_protocol::mqtt
{
enum class RetainAsPublished : std::uint8_t
{
    discard,
    retain
};
} // namespace toad::communication_protocol::mqtt