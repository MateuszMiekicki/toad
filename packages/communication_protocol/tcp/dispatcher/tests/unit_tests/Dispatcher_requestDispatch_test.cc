#include "dispatcher_mock/Broker_mock.hh"
#include "dispatcher_mock/Hub_mock.hh"
#include "dispatcher_mock/Notifier_mock.hh"
#include "dispatcher_mock/Requester_mock.hh"
#include "toad/communication_protocol/tcp/dispatcher/Dispatcher.hh"
#include <gtest/gtest.h>

class DispatcherFixture : public ::testing::Test
{
  protected:
    toad::communication_protocol::tcp::Dispatcher sut;
    HubMock hub_;
    BrokerMock broker_;
    RequesterMock requester_;
    NotifierMock notifier_;

    DispatcherFixture() : sut(hub_, broker_, requester_, notifier_)
    {
    }

    const toad::communication_protocol::tcp::Message::clientId_t clientId = "client_id";
    const toad::communication_protocol::tcp::Payload payload{"{}",
                                                             toad::communication_protocol::tcp::Payload::Type::json};
    const toad::communication_protocol::tcp::Message requestMessage{
        clientId,
        toad::communication_protocol::tcp::Message::Type::request,
        toad::communication_protocol::tcp::Message::Purpose::unknown,
        payload};
    const toad::communication_protocol::tcp::Message responseMessage{
        clientId,
        toad::communication_protocol::tcp::Message::Type::response,
        toad::communication_protocol::tcp::Message::Purpose::unknown,
        payload};

    toad::communication_protocol::tcp::Message
    createMessage(const toad::communication_protocol::tcp::Message::Type &type)
    {
        return toad::communication_protocol::tcp::Message{clientId,
                                                          type,
                                                          toad::communication_protocol::tcp::Message::Purpose::unknown,
                                                          payload};
    }
};

TEST_F(DispatcherFixture, whenPopMessageIsRequestShouldSendResponseByBrokerTcp)
{
    const auto message = createMessage(toad::communication_protocol::tcp::Message::Type::request);
    ON_CALL(hub_, pop()).WillByDefault(testing::Return(message));
    EXPECT_CALL(broker_, send(message));
    sut.dispatch();
}

TEST_F(DispatcherFixture, whenPopMessageIsResponseShouldSendResponseByRequester)
{
    const auto message = createMessage(toad::communication_protocol::tcp::Message::Type::response);
    ON_CALL(hub_, pop()).WillByDefault(testing::Return(message));
    EXPECT_CALL(requester_, send(message));
    sut.dispatch();
}

TEST_F(DispatcherFixture, whenPopMessageIsReportShouldSendResponseByNotifier)
{
    const auto message = createMessage(toad::communication_protocol::tcp::Message::Type::report);
    ON_CALL(hub_, pop()).WillByDefault(testing::Return(message));
    EXPECT_CALL(notifier_, send(message));
    sut.dispatch();
}