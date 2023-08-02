#pragma once
#include <string>

namespace toad::communication_protocol::tcp
{
class Payload;
std::string serialize(const Payload &);
} // namespace toad::communication_protocol::tcp