#include "SubscriptionManagerTestFixture.hh"

using toad::communication_protocol::mqtt::Connection;
using toad::communication_protocol::mqtt::Subscription;

TEST_F(SubscriptionManagerTestFixture, addingNewSubscriberShouldIncreaseNumberOfActiveSubscribersByOne)
{
    auto subsciber = std::make_shared<Connection>(nullptr);
    Subscription subscriptionTopicTest{subsciber, "test", {}};
    sut.subscribe(subscriptionTopicTest);

    ASSERT_EQ(sut.getNumberActiveSubscribers(), 1);
}

TEST_F(SubscriptionManagerTestFixture,
       subscribingToSameTopicSecondTimeBySameSubscriberShouldNotIncreaseNumberOfActiveSubscribers)
{
    auto subsciber = std::make_shared<Connection>(nullptr);
    Subscription subscriptionTopicTest{subsciber, "test", {}};
    sut.subscribe(subscriptionTopicTest);
    Subscription subscriptionTopicTestSecondTime{subsciber, "test", {}};
    sut.subscribe(subscriptionTopicTestSecondTime);

    ASSERT_EQ(sut.getNumberActiveSubscribers(), 1);
}

TEST_F(SubscriptionManagerTestFixture,
       subscribingToAnotherTopicByExistingSubscriberShouldNotIncreaseNumberOfActiveSubscribers)
{
    auto subsciber = std::make_shared<Connection>(nullptr);
    Subscription subscriptionTopicTest{subsciber, "test", {}};
    sut.subscribe(subscriptionTopicTest);
    Subscription subscriptionTopicConfig{subsciber, "config", {}};
    sut.subscribe(subscriptionTopicConfig);

    ASSERT_EQ(sut.getNumberActiveSubscribers(), 1);
}

TEST_F(SubscriptionManagerTestFixture, twoDifferentSubscribersSubscribingToSameTopicShouldIncreaseSubscriberCountToTwo)
{
    auto subscriberAnna = std::make_shared<Connection>(nullptr);
    Subscription subscriptionTopicTest{subscriberAnna, "test", {}};
    sut.subscribe(subscriptionTopicTest);

    auto subscriberJohn = std::make_shared<Connection>(nullptr);
    Subscription subscriptionTopicConfig{subscriberJohn, "test", {}};
    sut.subscribe(subscriptionTopicConfig);

    ASSERT_EQ(sut.getNumberActiveSubscribers(), 2);
}

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
