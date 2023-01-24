#pragma once
#include <mqtt/common_type.hpp>
#include <memory>

namespace toad::broker::mqtt
{
class Session
{
    private:
    using connection_t = std::shared_ptr<MQTT_NS::server<>::endpoint_t>;
  public:
    Session(const Session&) = delete;
    Session& operator=(const Session&) = delete;

    ~Session();
    Session(Session&&);
    Session& operator=(Session&&);


};
} // namespace toad::server::broker
