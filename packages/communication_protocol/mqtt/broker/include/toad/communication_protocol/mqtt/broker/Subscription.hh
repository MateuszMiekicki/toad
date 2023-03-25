#pragma once
#include "toad/communication_protocol/mqtt/broker/Connection.hh"

#include <string_view>

namespace toad::communication_protocol::mqtt
{
using topic_t = std::string_view;
class SubscriptionOptions;

class Subscription
{
  private:
  public:
    std::shared_ptr<Connection> connection_;
    topic_t topic_;
    SubscriptionOptions subscriptionOptions_;

    Subscription(const std::shared_ptr<Connection>&&, const topic_t&, const SubscriptionOptions&)
};
} // namespace toad::communication_protocol::mqtt
