#pragma once

namespace toad::communication_protocol::mqtt::mqtt_broker::interface
{
class Mqtt
{
  public:
    virtual ~Mqtt() = default;
    virtual bool start() = 0;
    virtual bool stop() = 0;
    virtual bool restart() = 0;
};
} // namespace toad::communication_protocol::mqtt::mqtt_broker::interface