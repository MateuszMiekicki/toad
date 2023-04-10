#pragma once
#include "toad/communication_protocol/mqtt/broker/PublishOptions.hh"
#include <fmt/format.h>

template<>
struct fmt::formatter<toad::communication_protocol::mqtt::PublishOptions>
{
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(const toad::communication_protocol::mqtt::PublishOptions& publishOptions, FormatContext& ctx)
    {
        return format_to(ctx.out(), "B!");
    }
};