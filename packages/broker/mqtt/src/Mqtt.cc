#include "toad/broker/mqtt/Mqtt.hh"

toad::broker::Mqtt::Mqtt(toad::server::interface::Server *a) : server_(a)
{

}
namespace toad::broker
{
Mqtt::~Mqtt()
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
