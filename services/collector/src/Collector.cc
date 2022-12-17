#include "toad/broker/mqtt/Mqtt.hh"
#include "toad/server/server/interface/Server.hh"
#include "toad/server/server/Endpoint.hh"
#include "toad/server/tcp/Tcp.hh"

int main()
{
    toad::server::Endpoint endpoint{"", 5432};
    std::unique_ptr<toad::server::interface::Server> server = 
        std::make_unique<toad::server::Tcp>(std::move(endpoint));
    std::unique_ptr<toad::broker::interface::Mqtt> mqtt = std::make_unique<toad::broker::Mqtt>(std::move(server));
    mqtt->start();
}