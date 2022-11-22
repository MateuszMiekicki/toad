#include <optional>
#include <string>
#include <toad/data_reader/environment_variable/EnvironmentVariable.hh>

namespace toad::data_reader
{
std::optional<std::string> getEnvironmentVariable(const std::string &name)
{
    if(const auto environmentVariable = std::getenv(name.data()))
    {
        return environmentVariable;
    }
    INFO_LOG("Environment variable \"{}\" not found", name);
    return std::nullopt;
}
} // namespace toad::data_reader
