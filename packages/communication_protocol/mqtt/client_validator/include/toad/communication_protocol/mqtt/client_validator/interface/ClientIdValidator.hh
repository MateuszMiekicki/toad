#pragma once
#include <string_view>

namespace toad::communication_protocol::mqtt
{
using clientId_t = std::string_view;
} // namespace toad::communication_protocol::mqtt

namespace toad::communication_protocol::mqtt::interface
{
class ClientIdValidator
{
  public:
    virtual ~ClientIdValidator() = default;
    virtual bool check(const clientId_t&) const = 0;
};
} // namespace toad::communication_protocol::mqtt::interface