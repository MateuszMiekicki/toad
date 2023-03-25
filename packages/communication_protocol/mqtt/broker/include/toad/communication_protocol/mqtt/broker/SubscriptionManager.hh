#pragma once

namespace toad::communication_protocol::mqtt
{
class Subscription;

class SubscriptionManager
{
  private:
  public:
    void publish(const topic_t&, const message_t&, );
    void subscribe(const Subscription&);
    void unsubscribe();
};
} // namespace toad::communication_protocol::mqtt