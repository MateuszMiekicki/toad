#include "toad/network/endpoint/Endpoint.hh"

namespace toad::network
{
Endpoint::Endpoint() : endpoint_(boost::asio::ip::address::from_string("0.0.0.0"), 1883)
{
}

Endpoint::Endpoint(const ipAddress_t& address, port_t port) :
    endpoint_(boost::asio::ip::address::from_string(address), port)
{
}

endpoint_t Endpoint::endpoint() const
{
    return endpoint_;
}
} // namespace toad::network
