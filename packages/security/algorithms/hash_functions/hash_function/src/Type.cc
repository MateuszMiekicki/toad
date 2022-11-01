#include <iostream>
#include <security/algorithms/hash_functions/hash_function/Type.hh>
#include <security/algorithms/hash_functions/interface/HashFunction.hh>

namespace
{
std::string toString(toad::security::algorithms::hash_functions::Type type)
{
    using namespace toad::security::algorithms::hash_functions;
    switch(type)
    {
        case Type::sha3_512:
        {
            return "hash_functions::Type::sha3_512";
        }
        default:
        {
            return "undefined";
        }
    }
}
} // namespace

namespace toad::security::algorithms::hash_functions
{
std::ostream &operator<<(std::ostream &os, Type type)
{
    os << toString(type);
    return os;
}

bool operator==(Type lhs, Type rhs)
{
    return lhs == rhs;
}

bool operator!=(Type lhs, Type rhs)
{
    return !(lhs == rhs);
}
} // namespace toad::security::algorithms::hash_functions