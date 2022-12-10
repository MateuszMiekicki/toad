#pragma once
// #include "toad/server/server/Logger.hh"

#include <cstdio>
#include <string_view>

namespace toad::server
{
using Address = std::string_view;
using Port = std::uint16_t;

struct Endpoint
{
    const Address address;
    const Port port;
};
} // namespace toad::server

// template<>
// struct fmt::formatter<toad::server::Endpoint>
// {
//     constexpr auto parse(format_parse_context& ctx)
//     {
//         return ctx.begin();
//     }

//     auto format(const toad::server::Endpoint& ep, format_context& ctx) const -> decltype(ctx.out())
//     {
//         return format_to(ctx.out(), "\"Endpoint\": {\"address\":{}, \"port\":{}})", ep.address.data(), ep.port);
//     }
// };