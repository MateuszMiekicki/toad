#pragma once
#include "toad/communication_protocol/tcp/message/Hub.hh"
#include <gmock/gmock.h>

struct HubMock : public toad::communication_protocol::tcp::Hub
{
    virtual ~HubMock() = default;
    MOCK_METHOD(void, push, (const toad::communication_protocol::tcp::Message &), (override));
    MOCK_METHOD(toad::communication_protocol::tcp::Message, pop, (), (override));
};