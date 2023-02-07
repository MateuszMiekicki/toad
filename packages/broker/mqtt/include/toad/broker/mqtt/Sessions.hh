#pragma once
#include <set>
#include "toad/broker/mqtt/Session.hh"
namespace toad::broker::mqtt
{
class Sessions
{
  // bool operator<(const Session&);
  std::set<Session> sessions_;
  public:
    // Sessions(const Sessions&) = delete;
    // Sessions& operator=(const Sessions&) = delete;
    Sessions() =default;
    ~Sessions()=default;
    // Sessions(Sessions&&);
    // Sessions& operator=(Sessions&&);
    
    bool addSession(Session);
    bool closeSession(Session);
};
} // namespace toad::server::broker
