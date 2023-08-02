#pragma once
#include "toad/communication_protocol/tcp/message/Message.hh"
#include <string>

namespace toad::communication_protocol::tcp
{
std::string serialize(Message::Purpose);
} // namespace toad::communication_protocol::tcp
