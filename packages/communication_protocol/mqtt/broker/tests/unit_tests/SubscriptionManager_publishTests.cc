#include "SubscriptionManagerTestFixture.hh"
#include "toad/communication_protocol/mqtt/broker/Connection.hh"
#include "toad/communication_protocol/mqtt/broker/SubscriptionManager.hh"

using toad::communication_protocol::mqtt::Connection;
using toad::communication_protocol::mqtt::content_t;
using toad::communication_protocol::mqtt::Duplicate;
using toad::communication_protocol::mqtt::PublishOptions;
using toad::communication_protocol::mqtt::QualityOfService;
using toad::communication_protocol::mqtt::RetainAsPublished;
using toad::communication_protocol::mqtt::Subscription;
using toad::communication_protocol::mqtt::topic_t;

using ::testing::StrictMock;

class MockSubscriber : public Connection
{
  public:
    MockSubscriber() : Connection(nullptr)
    {
    }

    MOCK_METHOD(void, publish, (topic_t, content_t, const PublishOptions&), (override));
};

TEST_F(SubscriptionManagerTestFixture, publicationOnSubscribedTopicShouldTriggerPublicationWithConcreteCustomer)
{
    auto subscriber = std::make_shared<MockSubscriber>();
    sut.subscribe({subscriber, "test_topic", {}});

    EXPECT_CALL(*subscriber, publish("test_topic", "content", testing::_));
    sut.publish("test_topic", "content", {QualityOfService::atMostOnce});
}

TEST_F(SubscriptionManagerTestFixture, twoClientsSubscribingToTheSameTopicShouldGetTheSamePayloadAfterPublication)
{
    auto subscriber1 = std::make_shared<MockSubscriber>();
    auto subscriber2 = std::make_shared<MockSubscriber>();
    const auto topic = "test_topic";
    const auto content = "content";
    sut.subscribe({subscriber1, topic, {}});
    sut.subscribe({subscriber2, topic, {}});

    EXPECT_CALL(*subscriber1, publish(topic, content, testing::_));
    EXPECT_CALL(*subscriber2, publish(topic, content, testing::_));
    sut.publish(topic, content, {QualityOfService::atMostOnce});
}

struct QoSForPublicationAndSubscription
{
    QualityOfService forPublish;
    QualityOfService forSubscribe;
    QualityOfService expected;
};

class SubscriptionManagerPublicationQoSSelectionParameterizedTestFixture :
    public SubscriptionManagerTestFixture,
    public ::testing::WithParamInterface<QoSForPublicationAndSubscription>
{
};

TEST_P(SubscriptionManagerPublicationQoSSelectionParameterizedTestFixture,
       publishedMessageShouldBeOfLowestQoSSelectedFromPublishAndSubscribeOptions)
{
    const auto& [forPublish, forSubscribe, expected] = GetParam();
    auto subscriber = std::make_shared<MockSubscriber>();
    sut.subscribe({subscriber, "test_topic", {forSubscribe}});

    EXPECT_CALL(*subscriber,
                publish(testing::_, testing::_, PublishOptions{expected, RetainAsPublished::discard, Duplicate::no}));
    sut.publish("test_topic", "content", {forPublish});
}

INSTANTIATE_TEST_SUITE_P(QoSForPublicationAndSubscription,
                         SubscriptionManagerPublicationQoSSelectionParameterizedTestFixture,
                         testing::Values(QoSForPublicationAndSubscription{QualityOfService::atMostOnce,
                                                                          QualityOfService::exactlyOnce,
                                                                          QualityOfService::atMostOnce},
                                         QoSForPublicationAndSubscription{QualityOfService::exactlyOnce,
                                                                          QualityOfService::atMostOnce,
                                                                          QualityOfService::atMostOnce}));
