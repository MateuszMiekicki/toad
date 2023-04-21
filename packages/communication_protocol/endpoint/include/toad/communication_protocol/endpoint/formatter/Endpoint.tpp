#pragma once
#include <fmt/format.h>

template<>
struct fmt::formatter<toad::communication_protocol::Endpoint>
{
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(const toad::communication_protocol::Endpoint& endpoint, FormatContext& ctx)
    {
        return format_to(ctx.out(), "\"endpoint\": {{\"address\": \"{}\", \"port\": \"{}\"}}",endpoint.endpoint().address().to_string(),endpoint.endpoint().port()  );
    }
};