#include <communication/protocols/types/server_details/ServerDetails.hh>
#include <iostream>

namespace toad::communication::protocols::types
{
ServerDetails::ServerDetails(const Address address, Port port) : address_{address}, port_{port}
{
}

Address ServerDetails::getAddress() const
{
    return address_;
}

Port ServerDetails::getPort() const
{
    return port_;
}

Address ServerDetails::getFullAddress() const
{
    return address_ + ":" + std::to_string(port_);
}

std::ostream& operator<<(std::ostream& os, const ServerDetails& serverDetails)
{
    os << serverDetails.getFullAddress();
    return os;
}

bool operator==(const ServerDetails& lhs, const ServerDetails& rhs)
{
    return lhs == rhs;
}

bool operator!=(const ServerDetails& lhs, const ServerDetails& rhs)
{
    return !(lhs == rhs);
}
} // namespace toad::communication::protocols::types