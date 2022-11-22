#include <toad/Logger.hh>
#include <toad/data_reader/environment_variable/ParseEnvironmentVariable.hh>
#include <optional>
#include <string>
#include <string_view>
#include <algorithm>

namespace
{
enum class EnvironmentVariableInputType
{
    plain,
    optional,
    error
};

EnvironmentVariableInputType identifyTypeOfInput(const std::string& input)
{
    if(input.find(":") not_eq std::string::npos)
    {
        return EnvironmentVariableInputType::optional;
    }
    if(input.find(":?") not_eq std::string::npos)
    {
        return EnvironmentVariableInputType::error;
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

bool isBeginAndEndCorrect(const std::string& input, const std::string& expectedBegin="${", const std::string& expectedEnd="}")
{
    return input.substr(0, expectedBegin.length()) == expectedBegin &&
    input.substr(input.length()-expectedEnd.length(), expectedEnd.length())==expectedEnd;
}

bool hasWhiteSpace(const std::string& input)
{
    return input.find(" ") not_eq std::string::npos;
}

bool hasOptionalParameterInCorrectFormat(const std::string& input)
{
    const auto pos = input.find(":");
    INFO_LOG(pos);
    return false;
    if(std::isspace(input.at(pos-1)) or std::isspace(input.at(pos+1)))
    {
        return false;
    }
    if(const auto optionalValue = input.substr(pos, input.length());
    optionalValue.length()>2)
    {
        return true;
    }
    return false;
}

bool hasMandatoryParameterInCorrectFormat(const std::string& input)
{
    const auto pos = input.find(":?");
    if(hasWhiteSpace(input.substr(0, pos)))
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
        }break;
        case EnvironmentVariableInputType::optional:
        {
            if(not hasWhiteSpace(input) and hasOptionalParameterInCorrectFormat(input))
            {
                return true;
            }
        }break;
        case EnvironmentVariableInputType::error:
        {
            if(hasMandatoryParameterInCorrectFormat(input))
            {
                return true;
            }
        }break;
        default:
        {
            return false;
        }
    }
    return false;
}
} // namespace toad::data_reader