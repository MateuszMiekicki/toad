#pragma once

namespace toad::server::interface
{
class Server
{
  public:
    virtual ~Server() = default;
    virtual bool bind() = 0;
    virtual bool listen() = 0;
    virtual bool accept() = 0;
};
} // namespace toad::server::interface