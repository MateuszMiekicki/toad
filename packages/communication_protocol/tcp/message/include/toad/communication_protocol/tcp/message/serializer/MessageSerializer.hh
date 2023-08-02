#pragma once
#include <string>

namespace toad::communication_protocol::tcp
{
class Message;
std::string serialize(const Message &);
} // namespace toad::communication_protocol::tcp