#include "toad/communication_protocol/endpoint/Endpoint.hh"
#include "toad/communication_protocol/tcp/broker/Broker.hh"
#include "toad/communication_protocol/tcp/dispatcher/Dispatcher.hh"
#include "toad/communication_protocol/tcp/message/Hub.hh"
#include "toad/communication_protocol/tcp/requester/Requester.hh"

int main()
{
    toad::communication_protocol::tcp::Hub hub;
    auto endpointForRequester = toad::communication_protocol::Endpoint("0.0.0.0", 5571);
    toad::communication_protocol::tcp::Requester requester(endpointForRequester, hub);
    auto endpointForTcpBroker = toad::communication_protocol::Endpoint("0.0.0.0", 5570);
    auto server = toad::communication_protocol::tcp::Broker(endpointForTcpBroker, hub);
    std::thread th(
        [&]()
        {
        requester.start();
    });
    std::thread th2(
        [&]()
        {
        server.start();
    });
    std::thread th3(
        [&]()
        {
        auto dispatcher = toad::communication_protocol::tcp::Dispatcher(hub, server, requester);
        dispatcher.start();
    });

    th.join();
    th2.join();
    return 0;
}
