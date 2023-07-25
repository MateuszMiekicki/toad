#pragma once
#include <cstdint>

namespace toad::external_interface::types
{
enum class Purpose : std::uint8_t
{
    unknown,
    failure,
    configuration,
    alert
};
} // namespace toad::external_interface::types