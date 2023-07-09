#include "toad/communication_protocol/endpoint/Endpoint.hh"

namespace toad::communication_protocol
{
Endpoint::Endpoint(const ipAddress_t& address, port_t port) :
    endpoint_(boost::asio::ip::address::from_string(address), port)
{
}

endpoint_t Endpoint::endpoint() const
{
    return endpoint_;
}
} // namespace toad::communication_protocol
