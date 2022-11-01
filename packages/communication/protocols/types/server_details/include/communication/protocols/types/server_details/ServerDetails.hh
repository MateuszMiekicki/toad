#pragma once
#include <iosfwd>
#include <string>

namespace toad::communication::protocols::types
{
using Port = uint16_t;
using Address = std::string;

class ServerDetails
{
    const Address address_;
    const Port port_;

  public:
    ServerDetails() = delete;
    ServerDetails(const Address address, Port port);

    Address getAddress() const;
    Port getPort() const;
    Address getFullAddress() const;

    friend std::ostream &operator<<(std::ostream &, const ServerDetails &);
    friend bool operator==(const ServerDetails &, const ServerDetails &);
    friend bool operator!=(const ServerDetails &, const ServerDetails &);
};
} // namespace toad::communication::protocols::types