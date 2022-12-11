#pragma once
#include "toad/server/server/Endpoint.hh"
#include "toad/server/server/interface/Server.hh"

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/context.hpp>
#include <memory>
#ifdef _WIN32
#include <windows.h>
#include <winsock2.h>
#endif

namespace toad::server
{
class Tcp : public interface::Server
{
  private:
    boost::asio::ip::tcp::endpoint endpoint_;
    std::unique_ptr<boost::asio::ssl::context> sslContext_{nullptr};

  public:
    Tcp(const Tcp&) = delete;
    Tcp& operator=(const Tcp&) = delete;

    ~Tcp();
    Tcp(Tcp&&);
    Tcp& operator=(Tcp&&);
    Tcp(const Endpoint&);
    Tcp(const Endpoint&, std::unique_ptr<boost::asio::ssl::context>);

    bool bind() override;
    bool listen() override;
    bool accept() override;
};
} // namespace toad::server
