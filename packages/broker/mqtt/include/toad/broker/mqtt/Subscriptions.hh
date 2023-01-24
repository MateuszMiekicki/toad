// #pragma once
// #include "toad/broker/mqtt/Topic.hh"
// #include "toad/broker/mqtt/Session.hh"
// #include "toad/broker/mqtt/SubscriptionOptions.hh"

// #include <boost/multi_index_container.hpp>
// #include <boost/multi_index/ordered_index.hpp>
// #include <boost/multi_index/member.hpp>
// #include <boost/multi_index/composite_key.hpp>

// namespace toad::broker::mqtt
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
