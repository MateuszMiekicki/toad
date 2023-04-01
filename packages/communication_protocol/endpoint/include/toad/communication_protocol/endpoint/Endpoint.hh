#pragma once
#include <boost/asio.hpp>
#include <cinttypes>
#include <string>

namespace toad::communication_protocol
{
using port_t = std::uint16_t;
using ipAddress_t = std::string;
using endpoint_t = boost::asio::ip::tcp::endpoint;

class Endpoint
{
  private:
    endpoint_t endpoint_;

  public:
    Endpoint();
    Endpoint(const ipAddress_t&, port_t);

    endpoint_t endpoint() const;
};
} // namespace toad::communication_protocol
