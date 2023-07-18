#include "toad/communication_protocol/endpoint/Endpoint.hh"
#include "toad/communication_protocol/tcp/broker/Broker.hh"
#include "toad/communication_protocol/tcp/dispatcher/Dispatcher.hh"
#include "toad/communication_protocol/tcp/message/Hub.hh"
#include "toad/communication_protocol/tcp/requester/Requester.hh"

int main()
{ 
    spdlog::set_level(spdlog::level::trace); // and this
    toad::communication_protocol::tcp::Hub hub;
    toad::communication_protocol::tcp::Requester requester(hub);
    auto endpoint = toad::communication_protocol::Endpoint("0.0.0.0", 5570);
    auto server = toad::communication_protocol::tcp::Broker(hub, endpoint);
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
