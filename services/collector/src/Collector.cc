// // Copyright Takatoshi Kondo 2019
// //
// // Distributed under the Boost Software License, Version 1.0.
// // (See accompanying file LICENSE_1_0.txt or copy at
// // http://www.boost.org/LICENSE_1_0.txt)

// #include <iostream>
// #include <iomanip>
// #include <set>

// #include <mqtt_server_cpp.hpp>

// #include <boost/lexical_cast.hpp>
// #include <boost/multi_index_container.hpp>
// #include <boost/multi_index/ordered_index.hpp>
// #include <boost/multi_index/member.hpp>
// #include <boost/multi_index/composite_key.hpp>

// namespace mi = boost::multi_index;

// using con_t = MQTT_NS::server<>::endpoint_t;
// using con_sp_t = std::shared_ptr<con_t>;

// int main(int argc, char** argv) {
//     if (argc != 2) {
//         std::cout << argv[0] << " port" << std::endl;
//         return -1;
//     }

//     MQTT_NS::setup_log();
//     boost::asio::io_context ioc;
//     auto s = MQTT_NS::server<>(
//         boost::asio::ip::tcp::endpoint(
//             boost::asio::ip::tcp::v4(),
//             boost::lexical_cast<std::uint16_t>(argv[1])
//         ),
//         ioc
//     );

//     s.set_error_handler(
//         [](MQTT_NS::error_code ec) {
//             std::cout << "error: " << ec.message() << std::endl;
//         }
//     );

//     s.set_accept_handler( // this handler doesn't depend on MQTT protocol version
//         [](con_sp_t spep) {

//             std::cout << "[server] accept" << std::endl;
//             spep->start_session();
//             spep->set_v5_connect_handler( // use v5 handler
//                 [spep]
//                 (MQTT_NS::buffer client_id,
//                  MQTT_NS::optional<MQTT_NS::buffer> const& username,
//                  MQTT_NS::optional<MQTT_NS::buffer> const& password,
//                  MQTT_NS::optional<MQTT_NS::will>,
//                  bool clean_start,
//                  std::uint16_t keep_alive,
//                  MQTT_NS::v5::properties /*props*/){
//                     using namespace MQTT_NS::literals;
//                     std::cout << "[server] client_id    : " << client_id << std::endl;
//                     std::cout << "[server] username     : " << (username ? username.value() : "none"_mb) <<
//                     std::endl; std::cout << "[server] password     : " << (password ? password.value() : "none"_mb)
//                     << std::endl; std::cout << "[server] clean_start  : " << std::boolalpha << clean_start <<
//                     std::endl; std::cout << "[server] keep_alive   : " << keep_alive << std::endl;
//                     spep->connack(false, MQTT_NS::v5::connect_reason_code::success);
//                     return true;
//                 }
//             );

//         }
//     );

//     s.listen();

//     ioc.run();
// }

#include "toad/communication_protocol/endpoint/Endpoint.hh"
#include "toad/communication_protocol/mqtt/broker/Broker.hh"
#include "toad/communication_protocol/mqtt/broker/BrokerEventHandler.hh"
#include "toad/communication_protocol/mqtt/broker/ClientConnectionHandler.hh"

#include <memory>
#include <thread>

int main()
{
    using namespace toad::communication_protocol;
    using namespace toad::communication_protocol::mqtt;
    std::unique_ptr<interface::ClientConnectionHandler> clientConnectionHandler =
        std::make_unique<ClientConnectionHandler>();
    std::unique_ptr<interface::BrokerEventHandler> brokerEventHandler =
        std::make_unique<BrokerEventHandler>(std::move(clientConnectionHandler));
    std::unique_ptr<interface::Broker> broker = std::make_unique<Broker>(Endpoint(), std::move(brokerEventHandler));
    broker->start();
}