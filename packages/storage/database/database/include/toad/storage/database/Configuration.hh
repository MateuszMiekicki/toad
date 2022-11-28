#pragma once
#include <fmt/ostream.h>
#include <ostream>
#include <string>

namespace toad::storage::database
{
using Port = short;

struct Configuration
{
    std::string host{};
    Port port = 0;
    std::string databaseName{};
    std::string user{};
    std::string password{};

    [[nodiscard]] auto to_string() const -> std::string
    {
        return "Configuration: {host: {" + host + "}, port: {" + std::to_string(port) + "}, database_name: {" +
               databaseName + "}, user: {" + user + "}}";
    }

    friend auto operator<<(std::ostream& os, const Configuration& configuration) -> std::ostream&
    {
        os << configuration.to_string();
        return os;
    }
};
} // namespace toad::storage::database

template<>
struct fmt::formatter<toad::storage::database::Configuration> : ostream_formatter
{
}; // NOLINT