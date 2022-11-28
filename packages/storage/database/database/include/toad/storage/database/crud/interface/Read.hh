#pragma once

namespace toad::storage::database::crud::interface
{
template<typename DataBaseObject>
class Read
{
  public:
    virtual ~Read() = default;
    virtual bool read(const DataBaseObject&) = 0;
};
} // namespace toad::storage::database::crud::interface
