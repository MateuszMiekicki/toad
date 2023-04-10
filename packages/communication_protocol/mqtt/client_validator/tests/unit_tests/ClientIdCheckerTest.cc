#include "toad/communication_protocol/mqtt/client_validator/ClientIdChecker.hh"
#include "toad/communication_protocol/mqtt/client_validator/Client.hh"
#include <gtest/gtest.h>

struct ClientIdCheckerFixture : public ::testing::Test
{
    toad::communication_protocol::mqtt::ClientIdChecker checker;
};

TEST_F(ClientIdCheckerFixture, ifClientIdIsNotEmptyItShouldReturnTrue)
{
    const toad::communication_protocol::mqtt::Client client{"client_id"};
    EXPECT_TRUE(checker.accept(client));
}

TEST_F(ClientIdCheckerFixture, ifClientIdIsEmptyItShouldReturnFalse)
{
    const toad::communication_protocol::mqtt::Client client{};
    EXPECT_FALSE(checker.accept(client));
}
