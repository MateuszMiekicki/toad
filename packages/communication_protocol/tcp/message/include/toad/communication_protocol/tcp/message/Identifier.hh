#pragma once
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <string>

namespace toad::communication_protocol::tcp
{
using uuid = std::string;

template<typename T>
struct Identifier
{
    Identifier() : id{boost::uuids::to_string(boost::uuids::random_generator()())}
    {
    }

    const uuid id;
};

using MessageId = Identifier<struct StrongTypeMessageId>;
} // namespace toad::communication_protocol::tcp