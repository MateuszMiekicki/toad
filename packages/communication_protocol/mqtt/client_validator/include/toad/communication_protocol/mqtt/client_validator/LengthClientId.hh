#pragma once
#include "toad/communication_protocol/mqtt/client_validator/interface//ClientIdValidator.hh"

namespace toad::communication_protocol::mqtt
{
class LengthClientId : public interface::ClientIdValidator
{
  public:
    bool check(const clientId_t&) const override;
};
} // namespace toad::communication_protocol::mqtt