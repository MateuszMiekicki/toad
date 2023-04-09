#pragma once
#include "toad/communication_protocol/mqtt/broker/Connection.hh"
#include "toad/communication_protocol/mqtt/broker/SubscriptionOptions.hh"
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index_container.hpp>
#include <string_view>

namespace toad::communication_protocol::mqtt
{
using subscriber_t = std::shared_ptr<Connection>;

struct Subscription
{
    subscriber_t subscriber_{nullptr};
    topic_t topic_;
    SubscriptionOptions subscriptionOptions_;
};

struct tag_con_topic
{
};

struct tag_topic
{
};

struct tag_con
{
};

// clang-format off
using subscriptions_t = boost::multi_index::multi_index_container<
    Subscription,
    boost::multi_index::indexed_by<
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<tag_con_topic>,
            boost::multi_index::composite_key<
                Subscription,
                BOOST_MULTI_INDEX_MEMBER(Subscription, subscriber_t, subscriber_),
                BOOST_MULTI_INDEX_MEMBER(Subscription, topic_t, topic_)
            >
        >,
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<tag_topic>,
            BOOST_MULTI_INDEX_MEMBER(Subscription, topic_t, topic_)
        >,
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<tag_con>,
            BOOST_MULTI_INDEX_MEMBER(Subscription, subscriber_t, subscriber_)
        >
    >
>;
// clang-format on
} // namespace toad::communication_protocol::mqtt
