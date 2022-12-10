#include "toad/server/server/Tcp.hh"

// #include "toad/server/server/Logger.hh"

namespace toad::server
{
Tcp::~Tcp()
{
}

Tcp::Tcp(const Endpoint& endpoint) : Tcp(endpoint, nullptr)
{
}

Tcp::Tcp(const Endpoint& endpoint, std::unique_ptr<boost::asio::ssl::context> sslContext) :
    endpoint_{boost::asio::ip::address::from_string(endpoint.address.data()), endpoint.port},
    sslContext_(std::move(sslContext))
{
}

bool Tcp::bind()
{
    return false;
}

bool Tcp::listen()
{
    return false;
}

bool Tcp::accept()
{
    return false;
}
} // namespace toad::server
