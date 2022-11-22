#pragma once
#include <optional>
#include <string>
#include <toad/Logger.hh>

namespace toad::data_reader::parser
{
bool isCorrectFormat(std::string input);
bool isPlainEnvironmentVariable(const std::string& input);
bool hasOptionalEnvironmentVariableSetting(const std::string& input);
bool isMandatoryEnvironmentVariableSetting(const std::string& input);
} // namespace toad::data_reader::parser
