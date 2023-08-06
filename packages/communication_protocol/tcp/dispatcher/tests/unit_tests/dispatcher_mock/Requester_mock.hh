#pragma once
#include "toad/communication_protocol/tcp/interface/Sender.hh"
#include <gmock/gmock.h>

struct RequesterMock : public toad::communication_protocol::tcp::interface::Sender
{
    virtual ~RequesterMock() = default;
    MOCK_METHOD(void, send, (const toad::communication_protocol::tcp::Message &), (override));
};