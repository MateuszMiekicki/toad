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
