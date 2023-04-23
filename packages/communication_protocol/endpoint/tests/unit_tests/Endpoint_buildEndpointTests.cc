#include "toad/communication_protocol/endpoint/Endpoint.hh"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace toad::communication_protocol;

struct EndpointData
{
    ipAddress_t ipAddress;
    port_t port;
};

class EndpointParameterizedTestFixture : public ::testing::TestWithParam<EndpointData>
{
};

TEST_P(EndpointParameterizedTestFixture, whenValidAddressIsPassedItShouldBeConvertedToEndpoint)
{
    const auto& [address, port] = GetParam();
    Endpoint endpoint(address, port);
    const auto& preparedEndpoint = endpoint.endpoint();
    ASSERT_EQ(preparedEndpoint.address().to_string(), address);
    ASSERT_EQ(preparedEndpoint.port(), port);
}

INSTANTIATE_TEST_SUITE_P(preparedDataForIPv4AndIPv6Endpoints,
                         EndpointParameterizedTestFixture,
                         testing::Values(EndpointData{"127.0.0.1", static_cast<port_t>(5432)},
                                         EndpointData{"::1", static_cast<port_t>(5432)}));
