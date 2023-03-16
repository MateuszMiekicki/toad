#pragma once
#include <mqtt_server_cpp.hpp>
#include <vector>

namespace toad::communication_protocol::mqtt
{
// todo(miekicki): refactoring, split into separate files; look at the start and start_session functions
class Connection
{
  public:
    using con_t = ::MQTT_NS::server<>::endpoint_t;
    using con_sp_t = std::shared_ptr<con_t>;
    using con_wp_t = std::weak_ptr<con_t>;

  private:
    con_sp_t connection_;

  public:
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;

    Connection(Connection&& con) : connection_{std::move(con.connection_)}
    {
    }

    Connection& operator=(Connection&& con)
    {
        connection_ = std::move(con.connection_);
        return *this;
    }

    Connection(con_sp_t&& con) : connection_(std::move(con))
    {
    }

    con_sp_t& get()
    {
        return connection_;
    }

    con_wp_t getWp()
    {
        return {connection_};
    }

    void start()
    {
        connection_->start_session(/*std::move(wp)*/);
    }
};

using connections_t = std::set<Connection::con_sp_t>;
} // namespace toad::communication_protocol::mqtt