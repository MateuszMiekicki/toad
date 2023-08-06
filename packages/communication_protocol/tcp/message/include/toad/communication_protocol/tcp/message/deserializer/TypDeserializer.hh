#pragma once
#include "toad/communication_protocol/tcp/message/Message.hh"
#include <string>

namespace toad::communication_protocol::tcp
{
Message::Type deserializeMessageType(const std::string &);
} // namespace toad::communication_protocol::tcp