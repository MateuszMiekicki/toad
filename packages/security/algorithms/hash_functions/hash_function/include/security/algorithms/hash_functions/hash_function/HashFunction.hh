#pragma once
#include <string>

namespace toad::security::algorithms::hash_functions
{
enum class Type;
class HashFunction
{
  public:
    ~HashFunction() = default;

    virtual std::string hash(const std::string &) const = 0;
    virtual Type type() const = 0;
};
} // namespace toad::security::algorithms::hash_functions