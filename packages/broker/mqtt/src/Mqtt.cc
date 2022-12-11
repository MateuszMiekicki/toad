#include "toad/broker/mqtt/Mqtt.hh"


namespace toad::broker
{
Mqtt::~Mqtt()
{
}

Mqtt::Mqtt(std::unique_ptr<toad::server::interface::Server> server) : server_(std::move(server))
{

}

bool Mqtt::start()
{
    return false;
}

bool Mqtt::stop()
{
    return false;
}

bool Mqtt::restart()
{
    return false;
}
} // namespace toad::broker
