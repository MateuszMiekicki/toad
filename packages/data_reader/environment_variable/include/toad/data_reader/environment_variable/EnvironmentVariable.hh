#pragma once
#include <optional>
#include <string>

namespace toad::data_reader
{
using EnvironmentVariable = std::optional<std::string>;
EnvironmentVariable getEnvironmentVariable(const std::string &name);
} // namespace toad::data_reader
