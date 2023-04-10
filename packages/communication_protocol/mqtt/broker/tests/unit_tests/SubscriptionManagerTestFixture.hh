#pragma once
#include "toad/communication_protocol/mqtt/broker/SubscriptionManager.hh"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

struct SubscriptionManagerTestFixture : public ::testing::Test
{
    toad::communication_protocol::mqtt::SubscriptionManager sut;
};
