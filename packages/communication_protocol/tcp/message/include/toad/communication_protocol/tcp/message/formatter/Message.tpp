#pragma once
#include "toad/communication_protocol/tcp/message/serializer/PurposeSerializer.hh"
#include "toad/communication_protocol/tcp/message/serializer/TypeSerializer.hh"
#include <fmt/format.h>

template<>
struct fmt::formatter<toad::communication_protocol::tcp::Message>
{
  private:
  public:
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(const toad::communication_protocol::tcp::Message&, FormatContext& ctx)
    {
        // return format_to(ctx.out(),
        //                  R"("message": {{"id": "{}", "client_id": "{}", "type": "{}", "purpose": "{}", {}}})",
        //                  message.getId(),
        //                  message.getClientId(),
        //                  toad::communication_protocol::tcp::serialize(message.getType()),
        //                  toad::communication_protocol::tcp::serialize(message.getPurpose()),
        //                  message.payload_);
        return format_to(ctx.out(), "");
    }
};