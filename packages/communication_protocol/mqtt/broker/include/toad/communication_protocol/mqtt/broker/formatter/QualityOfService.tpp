#pragma once
#include <fmt/format.h>

template<>
struct fmt::formatter<toad::communication_protocol::mqtt::QualityOfService>
{
    private:
         constexpr const char* toString(toad::communication_protocol::mqtt::QualityOfService qualityOfService)
    {
        using namespace toad::communication_protocol::mqtt;
        switch (qualityOfService)
        {
        case QualityOfService::atMostOnce:
            return "atMostOnce";
                case QualityOfService::atLeastOnce:
            return "atLeastOnce";
                    case QualityOfService::exactlyOnce:
            return "exactlyOnce";
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
  auto format(const toad::communication_protocol::mqtt::QualityOfService& qualityOfService, FormatContext& ctx)
  {
    return format_to(ctx.out(), std::string("mqtt::QualityOfService::")+toString(qualityOfService));
  }
};