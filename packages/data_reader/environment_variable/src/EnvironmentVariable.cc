#include <optional>
#include <string>
#include <toad/data_reader/environment_variable/EnvironmentVariable.hh>
#include <toad/data_reader/environment_variable/Logger.hh>

namespace toad::data_reader
{
auto getEnvironmentVariable(const std::string &name) -> EnvironmentVariable
{
    if(const auto environmentVariable = std::getenv(name.data()))
    {
        return environmentVariable;
    }
    WARN_LOG("Environment variable \"{}\" not found", name);
    return std::nullopt;
}
} // namespace toad::data_reader
