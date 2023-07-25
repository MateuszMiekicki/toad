#pragma once
#include <cstdint>

namespace toad::external_interface::types
{
enum class Type : std::uint8_t
{
    unknown,
    request,
    response,
    report
};
} // namespace toad::external_interface::types
