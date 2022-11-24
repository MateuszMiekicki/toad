#pragma once
#include <optional>
#include <string>

namespace toad::data_reader::parser
{
auto isCorrectFormat(std::string input) -> bool;
auto isPlainEnvironmentVariable(const std::string& input) -> bool;
auto hasOptionalEnvironmentVariableSetting(const std::string& input) -> bool;
auto isMandatoryEnvironmentVariableSetting(const std::string& input) -> bool;
} // namespace toad::data_reader::parser
