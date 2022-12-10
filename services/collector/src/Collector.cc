#include "toad/server/server/interface/Server.hh"
#include "toad/server/server/Tcp.hh"
#include <memory>

int main()
{
    const auto endpoint = toad::server::Endpoint{"", 5432};
    std::unique_ptr<toad::server::interface::Server> server =  std::make_unique<toad::server::Tcp>(endpoint);
}