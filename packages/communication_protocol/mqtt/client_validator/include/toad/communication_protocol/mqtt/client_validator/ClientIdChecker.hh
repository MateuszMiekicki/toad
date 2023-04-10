#pragma once
#include "toad/communication_protocol/mqtt/client_validator/interface//IncomingClientValidator.hh"

namespace toad::communication_protocol::mqtt
{
class ClientIdChecker : public interface::IncomingClientValidator
{
  public:
    bool accept(const Client&) const override;
};
} // namespace toad::communication_protocol::mqtt