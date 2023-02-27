#pragma once

namespace toad::communication_protocol::mqtt::interface
{
class Broker
{
  public:
    virtual ~Broker() = default;
    virtual bool start() = 0;
};
} // namespace toad::communication_protocol::mqtt::interface