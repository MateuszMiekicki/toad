#include "SubscriptionManagerTestFixture.hh"

using toad::communication_protocol::mqtt::Connection;
using toad::communication_protocol::mqtt::Subscription;

TEST_F(SubscriptionManagerTestFixture, unsubscribingFromOnlyTopicSubscribedToShouldReduceNumberOfActiveSubscribersByOne)
{
    auto subscriberAnna = std::make_shared<Connection>(nullptr);
    Subscription subscriptionTopicTest{subscriberAnna, "test", {}};
    sut.subscribe(subscriptionTopicTest);

    ASSERT_EQ(sut.getNumberActiveSubscribers(), 1);

    sut.unsubscribe(subscriptionTopicTest);
    ASSERT_EQ(sut.getNumberActiveSubscribers(), 0);
}

TEST_F(SubscriptionManagerTestFixture,
       unsubscribingFromOneOfTwoSubscribedTopicsShouldNotReduceNumberOfActiveSubscribers)
{
    auto subscriberAnna = std::make_shared<Connection>(nullptr);
    Subscription subscriptionTopicTest{subscriberAnna, "test", {}};
    sut.subscribe(subscriptionTopicTest);
    Subscription subscriptionTopicConfig{subscriberAnna, "config", {}};
    sut.subscribe(subscriptionTopicConfig);

    ASSERT_EQ(sut.getNumberActiveSubscribers(), 1);

    sut.unsubscribe(subscriptionTopicTest);
    ASSERT_EQ(sut.getNumberActiveSubscribers(), 1);
}

TEST_F(SubscriptionManagerTestFixture,
       unsubscribingClientFromTopicToWhichHeHasNotSubscribedShouldNotAffectOtherSubscribedTopics)
{
    auto subscriberAnna = std::make_shared<Connection>(nullptr);
    Subscription subscriptionTopicTest{subscriberAnna, "test", {}};
    sut.subscribe(subscriptionTopicTest);
    Subscription subscriptionTopicConfig{subscriberAnna, "config", {}};

    ASSERT_EQ(sut.getNumberActiveSubscribers(), 1);

    sut.unsubscribe(subscriptionTopicConfig);
    ASSERT_EQ(sut.getNumberActiveSubscribers(), 1);
}

TEST_F(SubscriptionManagerTestFixture,
       unsubscribingFromTopicByClientWhoIsNotSubscribedToAnythingShouldNotHaveEffectsOnOtherTopics)
{
    auto subscriberAnna = std::make_shared<Connection>(nullptr);
    Subscription subscriptionTopicTest{subscriberAnna, "test", {}};

    ASSERT_EQ(sut.getNumberActiveSubscribers(), 0);

    sut.unsubscribe(subscriptionTopicTest);
    ASSERT_EQ(sut.getNumberActiveSubscribers(), 0);
}
