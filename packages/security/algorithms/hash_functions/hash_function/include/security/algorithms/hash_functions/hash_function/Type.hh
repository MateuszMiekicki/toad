#pragma once
#include <iosfwd>

namespace toad::security::algorithms::hash_functions
{
enum class Type
{
    sha3_512
};
std::ostream &operator<<(std::ostream &, Type);
bool operator==(Type, Type);
bool operator!=(Type, Type);
} // namespace toad::security::algorithms::hash_functions