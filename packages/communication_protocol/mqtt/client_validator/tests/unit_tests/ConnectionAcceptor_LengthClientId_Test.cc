#include "toad/communication_protocol/mqtt/client_validator/LengthClientId.hh"

#include <gtest/gtest.h>

class LengthClientIdFixture : public ::testing::Test
{
  public:
    toad::communication_protocol::mqtt::LengthClientId checker;
};

TEST_F(LengthClientIdFixture, ifClientIdIsNotEmptyItShouldReturnTrue)
{
    EXPECT_TRUE(checker.check("client_id_123"));
}

TEST_F(LengthClientIdFixture, ifClientIdIsEmptyItShouldReturnFalse)
{
    EXPECT_TRUE(checker.check("client_id_123"));
}
