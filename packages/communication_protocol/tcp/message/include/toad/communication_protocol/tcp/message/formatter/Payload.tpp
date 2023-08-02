#pragma once
#include <fmt/format.h>

template<>
struct fmt::formatter<toad::communication_protocol::tcp::Payload>
{
  private:
    std::string serialize(const toad::communication_protocol::tcp::Payload::Type& type)
    {
        switch(type)
        {
            case toad::communication_protocol::tcp::Payload::Type::json:
                return "json";
            case toad::communication_protocol::tcp::Payload::Type::unknown:
            default:
                return "unknown";
        }
    }

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
                         serialize(payload.getType()),
                         payload.getPayload().size());
    }
};