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
                return "mqtt::Duplicate::no";
            case Duplicate::yes:
                return "mqtt::Duplicate::yes";
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
    auto format(const toad::communication_protocol::mqtt::PublishOptions& publishOptions, FormatContext& ctx)
    {
        return format_to(
            ctx.out(),
            R"("publish_options": {{"quality_of_service": "{}", "retain_as_published": "{}", "duplicate": "{}" }})",
            publishOptions.qualityOfService,
            publishOptions.retainAsPublished,
            toString(publishOptions.duplicate));
    }
};