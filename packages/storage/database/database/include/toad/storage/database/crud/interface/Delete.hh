#pragma once

namespace toad::storage::database::crud::interface
{
template<typename DataBaseObject>
class Delete
{
  public:
    virtual ~Delete() = default;
    virtual bool delete(const DataBaseObject&) = 0;
};
} // namespace toad::storage::database::crud::interface
