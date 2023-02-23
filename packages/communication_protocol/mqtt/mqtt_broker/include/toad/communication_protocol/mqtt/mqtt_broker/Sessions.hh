#pragma once
#include "toad/communication_protocol/mqtt/mqtt_broker/Session.hh"

#include <set>

namespace toad::communication_protocol::mqtt::mqtt_broker
{
class Sessions
{
    // bool operator<(const Session&);
    std::set<Session> sessions_;

  public:
    // Sessions(const Sessions&) = delete;
    // Sessions& operator=(const Sessions&) = delete;
    Sessions() = default;
    ~Sessions() = default;
    // Sessions(Sessions&&);
    // Sessions& operator=(Sessions&&);

    bool addSession(Session);
    bool closeSession(Session);
};
} // namespace toad::communication_protocol::mqtt::mqtt_broker
