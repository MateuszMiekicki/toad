#pragma once
#include <set>

namespace toad::broker::mqtt
{
class Session;
class Sessions
{
  bool operator<(const Session&);
  std::set<Session> sessions_;
  public:
    Sessions(const Sessions&) = delete;
    Sessions& operator=(const Sessions&) = delete;

    ~Sessions();
    Sessions(Sessions&&);
    Sessions& operator=(Sessions&&);
    
    bool addSession(Session&&);
    bool closeSession(Session&&);
};
} // namespace toad::server::broker
