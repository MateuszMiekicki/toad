#pragma once
#include <optional>
#include <string>

namespace toad::data_reader
{
using EnvironmentVariable = std::optional<std::string>;
auto getEnvironmentVariable(const std::string &name) -> EnvironmentVariable;
} // namespace toad::data_reader
