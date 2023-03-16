#pragma once

namespace toad::communication_protocol::mqtt::interface
{
// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
class Broker
{
  public:
    virtual ~Broker() = default;
    virtual bool start() = 0;
};
} // namespace toad::communication_protocol::mqtt::interface