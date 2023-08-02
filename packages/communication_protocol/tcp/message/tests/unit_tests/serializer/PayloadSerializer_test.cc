#include "toad/communication_protocol/tcp/message/Payload.hh"
#include "toad/communication_protocol/tcp/message/serializer/PayloadSerializer.hh"
#include <gtest/gtest.h>

namespace
{
struct PayloadAndExpectedJSON
{
    toad::communication_protocol::tcp::Payload payload;
    std::string expectedJson;
};
} // namespace

struct PayloadSerializerParameteizedTest : public ::testing::TestWithParam<PayloadAndExpectedJSON>
{
};

TEST_P(PayloadSerializerParameteizedTest, serialize)
{
    const auto& [payload, expectedJson] = GetParam();
    const auto serialized = toad::communication_protocol::tcp::serialize(payload);
    EXPECT_EQ(serialized, expectedJson);
}

INSTANTIATE_TEST_SUITE_P(PayloadSerializerParameteizedTestInstance,
                         PayloadSerializerParameteizedTest,
                         ::testing::Values(PayloadAndExpectedJSON{
                             toad::communication_protocol::tcp::PayloadFactory::createJson(R"({})"),
                             R"({})"}));