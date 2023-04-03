#pragma once
#include <optional>
#include <string>

namespace toad::communication_protocol::mqtt
{
using clientId_t = std::string;
using username_t = std::string;
using password_t = std::string;

struct AuthenticationData
{
    username_t username;
    password_t password;
};

using optionalAuthn = std::optional<AuthenticationData>;

struct Client
{
    clientId_t clientId;
    optionalAuthn authn{};
};
} // namespace toad::communication_protocol::mqtt