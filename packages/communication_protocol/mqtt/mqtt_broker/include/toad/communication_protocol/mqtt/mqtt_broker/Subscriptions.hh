// #pragma once
// #include "toad/communication_protocol/mqtt/mqtt_broker/Topic.hh"
// #include "toad/communication_protocol/mqtt/mqtt_broker/Session.hh"
// #include "toad/communication_protocol/mqtt/mqtt_broker/SubscriptionOptions.hh"

// #include <boost/multi_index_container.hpp>
// #include <boost/multi_index/ordered_index.hpp>
// #include <boost/multi_index/member.hpp>
// #include <boost/multi_index/composite_key.hpp>

// namespace toad::communication_protocol::mqtt::mqtt_broker
// {
// class Subscriptions
// {
//   private:
// using subscriptions_t = std::set<Topic>;

// subscriptions_t subscriptions_;
// public:
//     Subscriptions(const Subscriptions&) = delete;
//     Subscriptions& operator=(const Subscriptions&) = delete;

//     ~Subscriptions();
//     Subscriptions(Subscriptions&&);
//     Subscriptions& operator=(Subscriptions&&);
//     bool addTopic()
// }
// } // namespace toad::server::broker
