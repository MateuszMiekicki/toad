#include "toad/broker/mqtt/Sessions.hh"
#include "toad/broker/mqtt/Session.hh"

namespace toad::broker::mqtt
{
    bool Sessions::addSession(Session session)
    {
      sessions_.insert(session);
    }
    bool Sessions::closeSession(Session)
    {

    }
} // namespace toad::server::broker
