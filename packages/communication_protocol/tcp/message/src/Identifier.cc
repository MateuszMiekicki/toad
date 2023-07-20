#include "toad/communication_protocol/tcp/message/Identifier.hh"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace toad::communication_protocol::tcp
{
template<typename T>
Identifier<T>::Identifier() : id{boost::uuids::to_string(boost::uuids::random_generator()())}
{
}
Identifier<struct StrongTypeMessageId> id{};

} // namespace toad::communication_protocol::tcp