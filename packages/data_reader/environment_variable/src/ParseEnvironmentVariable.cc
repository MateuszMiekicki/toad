#include <algorithm>
#include <optional>
#include <string>
#include <string_view>
#include <toad/Logger.hh>
#include <toad/data_reader/environment_variable/ParseEnvironmentVariable.hh>

namespace
{
const auto beginFormat = std::string("${");
const auto endFormat = std::string("}");
const auto optionalDelimiter = std::string(":");
const auto mandatoryDelimiter = std::string(":?");

enum class EnvironmentVariableInputType
{
    plain,
    optional,
    mandatory
};

EnvironmentVariableInputType identifyTypeOfInput(const std::string& input)
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

bool isBeginAndEndCorrect(const std::string& input)
{
    return input.substr(0, beginFormat.length()) == beginFormat &&
           input.substr(input.length() - endFormat.length(), endFormat.length()) == endFormat;
}

bool hasWhiteSpace(const std::string& input)
{
    return input.find(" ") not_eq std::string::npos;
}

bool hasOptionalParameterInCorrectFormat(const std::string& input)
{
    const auto pos = input.find(optionalDelimiter);
    if(std::isspace(input.at(pos - optionalDelimiter.length())) or std::isspace(input.at(pos + 1)))
    {
        return false;
    }
    if(const auto optionalValue = input.substr(pos, input.length()); optionalValue.length() > beginFormat.length())
    {
        return true;
    }
    return false;
}

bool hasMandatoryParameterInCorrectFormat(const std::string& input)
{
    if(const auto variableWithDollarSignAndBrace = input.substr(0, input.find(mandatoryDelimiter));
       hasWhiteSpace(variableWithDollarSignAndBrace) or
       (variableWithDollarSignAndBrace.length() < (beginFormat.length() + mandatoryDelimiter.length())))
    {
        return false;
    }
    return true;
}
} // namespace

namespace toad::data_reader::parser
{
bool isCorrectFormat(std::string input)
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
