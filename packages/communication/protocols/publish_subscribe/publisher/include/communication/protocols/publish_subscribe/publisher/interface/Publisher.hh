#pragma once

namespace toad::communication::protocols::publish_subscribe::interface
{
class Publisher
{
  public:
    ~Publisher() = default;
    virtual void publish() = 0;
};
} // namespace toad::communication::protocols::publish_subscribe::interface