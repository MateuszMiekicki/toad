#pragma once
#include <fmt/format.h>
#include <string>

namespace toad::communication_protocol::tcp
{
std::string serialize(Message::Purpose);
std::string serialize(Message::Type);
} // namespace toad::communication_protocol::tcp

template<>
struct fmt::formatter<toad::communication_protocol::tcp::Message>
{
  public:
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(const toad::communication_protocol::tcp::Message& message, FormatContext& ctx)
    {
        return format_to(ctx.out(),
                         R"("message": {{"id": "{}", "client_id": "{}", "type": "{}", "purpose": "{}", {}}})",
                         message.getId(),
                         message.getClientId(),
                         toad::communication_protocol::tcp::serialize(message.getType()),
                         toad::communication_protocol::tcp::serialize(message.getPurpose()),
                         message.payload_);
    }
};