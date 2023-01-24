#pragma once

namespace toad::broker::mqtt::interface
{
class Mqtt
{
  public:
    virtual ~Mqtt() = default;
    virtual bool start() = 0;
    virtual bool stop() = 0;
    virtual bool restart() = 0;
};
} // namespace toad::broker::mqtt::interface