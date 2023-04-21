#pragma once
#include <fmt/format.h>

template<>
struct fmt::formatter<toad::communication_protocol::mqtt::RetainAsPublished>
{
  private:
    constexpr const char* toString(toad::communication_protocol::mqtt::RetainAsPublished retainAsPublished)
    {
        using namespace toad::communication_protocol::mqtt;
        switch(retainAsPublished)
        {
            case RetainAsPublished::discard:
                return "discard";
            case RetainAsPublished::retain:
                return "retain";
            default:
                return "undefined value";
        }
    }

  public:
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(const toad::communication_protocol::mqtt::RetainAsPublished& retainAsPublished, FormatContext& ctx)
    {
        return format_to(ctx.out(), std::string("mqtt::RetainAsPublished::") + toString(retainAsPublished));
    }
};