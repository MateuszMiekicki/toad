#pragma once
#include "toad/communication_protocol/tcp/interface/Sender.hh"
#include <gmock/gmock.h>

struct NotifierMock : public toad::communication_protocol::tcp::interface::Sender
{
    virtual ~NotifierMock() = default;
    MOCK_METHOD(void, send, (const toad::communication_protocol::tcp::Message &), (override));
};