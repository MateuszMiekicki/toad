#pragma once
#include "toad/communication_protocol/mqtt/broker/PublishOptions.hh"
#include <fmt/format.h>

namespace toad::communication_protocol::mqtt
{
template<>
struct fmt::formatter<PublishOptions>
{
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(const PublishOptions& publishOptions, FormatContext& ctx)
    {
        return format_to(ctx.out(), "B!");
    }
};
} // namespace toad::communication_protocol::mqtt