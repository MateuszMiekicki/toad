#include "toad/communication_protocol/endpoint/Endpoint.hh"
#include "toad/communication_protocol/tcp/broker/Broker.hh"
#include "toad/communication_protocol/tcp/dispatcher/Dispatcher.hh"
#include "toad/communication_protocol/tcp/message/Hub.hh"
#include "toad/communication_protocol/tcp/requester/Requester.hh"

int main()
{
    toad::communication_protocol::tcp::Hub hub;

    auto endpointForRequester = toad::communication_protocol::Endpoint("0.0.0.0", 5571);
    auto requester = toad::communication_protocol::tcp::Requester(endpointForRequester, hub);

    auto endpointForTcpBroker = toad::communication_protocol::Endpoint("0.0.0.0", 5570);
    auto brokerTcp = toad::communication_protocol::tcp::Broker(endpointForTcpBroker, hub);

    auto endpointForNotifier = toad::communication_protocol::Endpoint("0.0.0.0", 5572);
    auto notifier = toad::communication_protocol::tcp::Notifier(endpointForNotifier);

    std::thread requesterThread(
        [&]()
        {
        requester.start();
    });
    std::thread brokerTcpThread(
        [&]()
        {
        brokerTcp.start();
    });
    std::thread notifierThread(
        [&]()
        {
        notifier.start();
    });
    std::thread dispatcherThread(
        [&]()
        {
        auto dispatcher = toad::communication_protocol::tcp::Dispatcher(hub, brokerTcp, requester, notifier);
        while(true)
        {
            dispatcher.dispatch();
        }
    });
    requesterThread.join();
    brokerTcpThread.join();
    notifierThread.join();
    dispatcherThread.join();
}
