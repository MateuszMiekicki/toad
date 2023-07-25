#pragma once
#include <fmt/format.h>

template<>
struct fmt::formatter<toad::communication_protocol::tcp::Payload>
{
  private:
  public:
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(const toad::communication_protocol::tcp::Payload& payload, FormatContext& ctx)
    {
        return format_to(ctx.out(),
                         R"("payload": {{"type": "{}", "size": {}}})",
                         toad::communication_protocol::tcp::Payload::serialize(payload.getType()),
                         payload.getPayload().size());
    }
};