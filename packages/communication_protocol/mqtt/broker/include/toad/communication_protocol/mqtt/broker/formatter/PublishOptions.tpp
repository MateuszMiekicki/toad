#pragma once
#include <fmt/format.h>

template<>
struct fmt::formatter<toad::communication_protocol::mqtt::PublishOptions>
{
  private:
    constexpr const char* toString(toad::communication_protocol::mqtt::Duplicate duplicate)
    {
        using namespace toad::communication_protocol::mqtt;
        switch(duplicate)
        {
            case Duplicate::no:
                return "no";
            case Duplicate::yes:
                return "yes";
            default:
                return "undefined value";
        }
    }

    constexpr const char* toString(toad::communication_protocol::mqtt::PublishOptions )
    {
        using namespace toad::communication_protocol::mqtt;
        return  "";
    }
  public:
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(const toad::communication_protocol::mqtt::PublishOptions& publishOptions, FormatContext& ctx)
    {
        return format_to(ctx.out(), std::string("mqtt::PublishOptions") + toString(publishOptions));
    }
};