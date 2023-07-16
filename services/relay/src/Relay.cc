#include "toad/communication_protocol/endpoint/Endpoint.hh"
#include "toad/communication_protocol/tcp/broker/Broker.hh"
#include "toad/communication_protocol/tcp/message/Hub.hh"
#include "toad/communication_protocol/tcp/requester/Requester.hh"

int main()
{
    toad::communication_protocol::tcp::Hub hub;
    std::thread th(
        [&]()
        {
        toad::communication_protocol::tcp::Requester requester(hub);
        requester.start();
    });
    std::thread th2(
        [&]()
        {
        auto endpoint = toad::communication_protocol::Endpoint("0.0.0.0", 5570);
        auto server = toad::communication_protocol::tcp::Broker(hub, endpoint);
        server.start();
    });
    th.join();
    th2.join();
    return 0;
}
