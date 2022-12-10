#pragma once
#include "toad/broker/mqtt/interface/Mqtt.hh"
#include "toad/server/server/interface/Server.hh"
#include <memory>

namespace toad::broker
{
class Mqtt : public interface::Mqtt
{
  private:
  std::unique_ptr<toad::server::interface::Server> server_;

  public:
    Mqtt(const Mqtt&) = delete;
    Mqtt& operator=(const Mqtt&) = delete;

    ~Mqtt();
    Mqtt(Mqtt&&);
    Mqtt& operator=(Mqtt&&);
    Mqtt(server::interface::Server*);

    bool start() override;
    bool stop() override;
    bool restart() override;
};
} // namespace toad::server::broker
