#pragma once
#include <memory>

namespace toad::communication_protocol::mqtt
{
class Connection;
} // namespace toad::communication_protocol::mqtt

namespace toad::communication_protocol
{
class ErrorCode;
} // namespace toad::communication_protocol

namespace toad::communication_protocol::mqtt::interface
{
// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
class ClientConnectionHandler
{
  public:
    virtual ~ClientConnectionHandler() = default;
    virtual void onClose(std::shared_ptr<Connection>) = 0;
    virtual void onError(std::shared_ptr<Connection>) = 0;
    virtual void onConnect(std::shared_ptr<Connection>) = 0;
    virtual void onDisconnect(std::shared_ptr<Connection>) = 0;
    virtual void onPublish(std::shared_ptr<Connection>) = 0;
    virtual void onSubscribe(std::shared_ptr<Connection>) = 0;
    virtual void onUnsubscribe(std::shared_ptr<Connection>) = 0;
};
} // namespace toad::communication_protocol::mqtt::interface