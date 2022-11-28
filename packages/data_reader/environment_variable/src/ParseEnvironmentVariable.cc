#include <algorithm>
#include <optional>
#include <string>
#include <string_view>
#include <toad/data_reader/environment_variable/ParseEnvironmentVariable.hh>

namespace
{
const auto beginFormat = "${";
const auto endFormat = "}";
const auto optionalDelimiter = ":";
const auto mandatoryDelimiter = ":?";

enum class EnvironmentVariableInputType
{
    plain,
    optional,
    mandatory
};

auto identifyTypeOfInput(const std::string& input) -> EnvironmentVariableInputType
{
    if(input.find(mandatoryDelimiter) not_eq std::string::npos) 
    {
        return EnvironmentVariableInputType::mandatory;
    }
    if(input.find(optionalDelimiter) not_eq std::string::npos)
    {
        return EnvironmentVariableInputType::optional;
    }
    return EnvironmentVariableInputType::plain;
}

void ltrim(std::string& input)
{
    input.erase(input.begin(),
                std::find_if(input.begin(),
                             input.end(),
                             [](unsigned char ch)
                             {
        return !std::isspace(ch);
                }));
}

void rtrim(std::string& input)
{
    input.erase(std::find_if(input.rbegin(),
                             input.rend(),
                             [](unsigned char ch)
                             {
        return !std::isspace(ch);
                }).base(),
                input.end());
}

void trim(std::string& input)
{
    rtrim(input);
    ltrim(input);
}

auto isBeginAndEndCorrect(const std::string& input) -> bool
{
    return input.substr(0, std::string(beginFormat).length()) == beginFormat &&
           input.substr(input.length() - std::string(endFormat).length(), std::string(endFormat).length()) == endFormat;
}

auto hasWhiteSpace(const std::string& input) -> bool
{
    return input.find(" ") not_eq std::string::npos;
}

auto hasOptionalParameterInCorrectFormat(const std::string& input) -> bool
{
    const auto pos = input.find(optionalDelimiter);
    if(std::isspace(input.at(pos - std::string(optionalDelimiter).length())) or std::isspace(input.at(pos + 1)))
    {
        return false;
    }
    if(const auto optionalValue = input.substr(pos, input.length());
       optionalValue.length() > std::string(beginFormat).length())
    {
        return true;
    }
    return false;
}

auto hasMandatoryParameterInCorrectFormat(const std::string& input) -> bool
{
    if(const auto variableWithDollarSignAndBrace = input.substr(0, input.find(mandatoryDelimiter));
       hasWhiteSpace(variableWithDollarSignAndBrace) or
       (variableWithDollarSignAndBrace.length() <
        (std::string(beginFormat).length() + std::string(mandatoryDelimiter).length())))
    {
        return false;
    }
    return true;
}
} // namespace

namespace toad::data_reader::parser
{
auto isCorrectFormat(std::string input) -> bool
{
    trim(input);
    if(not isBeginAndEndCorrect(input))
    {
        return false;
    }
    switch(identifyTypeOfInput(input))
    {
        case EnvironmentVariableInputType::plain:
        {
            if(not hasWhiteSpace(input))
            {
                return true;
            }
        }
        break;
        case EnvironmentVariableInputType::optional:
        {
            if(not hasWhiteSpace(input) and hasOptionalParameterInCorrectFormat(input))
            {
                return true;
            }
        }
        break;
        case EnvironmentVariableInputType::mandatory:
        {
            if(hasMandatoryParameterInCorrectFormat(input))
            {
                return true;
            }
        }
        break;
        default:
        {
            return false;
        }
    }
    return false;
}
} // namespace toad::data_reader::parser
