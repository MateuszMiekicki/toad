#include "toad/server/server/Tcp.hh"
#include "toad/broker/mqtt/Mqtt.hh"
#include <memory>

int main()
{
    const auto endpoint = toad::server::Endpoint{"", 5432};
    std::unique_ptr<toad::server::interface::Server> server =  std::make_unique<toad::server::Tcp>(endpoint);
    std::unique_ptr<toad::broker::interface::Mqtt> mqttBroker = std::make_unique<toad::broker::Mqtt>(std::move(server));
}