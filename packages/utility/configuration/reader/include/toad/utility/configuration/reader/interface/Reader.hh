#pragma once
#include <string>

namespace toad::utility::configuration::interface
{
// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
class Reader
{
  public:
    virtual ~Reader() = default;
    virtual std::string read(const std::string&) = 0;
};
} // namespace toad::communication_protocol::mqtt::interface