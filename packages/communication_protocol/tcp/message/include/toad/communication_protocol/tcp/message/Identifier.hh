#pragma once
#include <string>

namespace toad::communication_protocol::tcp
{
using uuid = std::string;

template<typename T>
struct Identifier
{
    uuid id;
    Identifier();
};

using MessageId = Identifier<struct StrongTypeMessageId>;
} // namespace toad::communication_protocol::tcp