#pragma once

namespace toad::storage::database::crud::interface
{
template<typename DataBaseObject>
class Create
{
  public:
    virtual ~Create() = default;
    virtual bool create(const DataBaseObject&) = 0;
};
} // namespace toad::storage::database::crud::interface
