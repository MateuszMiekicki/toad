#pragma once

namespace toad::communication::protocols::publish_subscribe
{
class Topic;

class Subscriber
{
  public:
    virtual void subscribe(const Topic&) = 0;
};
} // namespace toad::communication::protocols::publish_subscribe