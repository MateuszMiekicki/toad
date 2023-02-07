#include "toad/broker/mqtt/Session.hh"

namespace toad::broker::mqtt
{
Session::Session(con_sp_t connection) : session_{connection}
{
}

bool Session::operator<(const Session&) const
{
    return true;
}

} // namespace toad::broker::mqtt
