#pragma once

namespace toad::storage::database::crud::interface
{
template<typename DataBaseObject>
class Update
{
  public:
    virtual ~Update() = default;
    virtual bool update(const DataBaseObject&) = 0;
};
} // namespace toad::storage::database::crud::interface
