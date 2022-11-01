#include <communication/protocols/publish_subscribe/client/Client.hh>

namespace toad::communication::protocols::publish_subscribe
{
Client::~Client()
{
    disconnect();
}

void Client::publish()
{
    return;
}

bool Client::connect()
{
    return false;
}

bool Client::disconnect()
{
    return false;
}

bool Client::reestablishConnection()
{
    return false;
}
} // namespace toad::communication::protocols::publish_subscribe