#pragma once
#include <optional>
#include <string>

namespace toad::data_reader
{
std::optional<std::string> getEnvironmentVariable(const std::string &name);
} // namespace toad::data_reader
