#include <gtest/gtest.h>
#include <toad/communication_protocol/tcp/message/Message.hh>
#include <toad/communication_protocol/tcp/message/serializer/MessageSerializer.hh>

namespace
{
struct MessageAndExpectedJSON
{
    toad::communication_protocol::tcp::Message message;
    std::string expectedJson;
};
} // namespace

struct MessageSerializerParameteizedTest : public ::testing::TestWithParam<MessageAndExpectedJSON>
{
};

TEST_P(MessageSerializerParameteizedTest, serialize)
{
    const auto& [message, expectedJson] = GetParam();
    const auto serialized_message = toad::communication_protocol::tcp::serialize(message);
    EXPECT_EQ(serialized_message, expectedJson);
}

INSTANTIATE_TEST_SUITE_P(
    MessageSerializerParameteizedTestInstance,
    MessageSerializerParameteizedTest,
    ::testing::Values(MessageAndExpectedJSON{
        toad::communication_protocol::tcp::Message{
                                                   "clinet_id", toad::communication_protocol::tcp::Message::Type::request,
                                                   toad::communication_protocol::tcp::Message::Purpose::getConfiguration,
                                                   toad::communication_protocol::tcp::Payload("payload",
                                                   toad::communication_protocol::tcp::Payload::Type::json)},
        R"({"type":"request","purpose":"get_configuration","payload":"payload"})"
}));