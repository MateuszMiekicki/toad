#pragma once
#include <toad/storage/database/Database.hh>
#include <memory>
#include <soci/soci.h>

namespace toad::storage::database
{
struct Configuration;
namespace postgresql
{
class PostgreSQL : public interface::Database
{
  private:
  std::unique_ptr<soci::session> session_;
  database::Configuration configuration_;

  auto closeConnection()->bool;
  public:
    PostgreSQL(Configuration);
    PostgreSQL(const PostgreSQL&) = delete;
    auto operator=(const PostgreSQL&) -> PostgreSQL& = delete;

    PostgreSQL(PostgreSQL&&) noexcept;
    auto operator=(PostgreSQL&&) noexcept -> PostgreSQL&;

    ~PostgreSQL() override ;

    auto connect() -> bool override;
    auto isConnected()-> bool override;
    auto reconnect()-> bool override;
    auto disconnect() -> bool override;
};
}
} // namespace toad::storage::database::postgresql
