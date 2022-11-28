#include <toad/storage/database/Configuration.hh>
#include <toad/storage/database/postgresql/PostgreSQL.hh>
#include <toad/storage/database/Logger.hh>
#include <soci/soci.h>

namespace toad::storage::database::postgresql
{
PostgreSQL::PostgreSQL(database::Configuration configuration): session_(std::make_unique<soci::session>()),
configuration_{std::move(configuration)}
{
    INFO_LOG("PostgreSQL configuration: {}", configuration);
}

PostgreSQL::PostgreSQL(PostgreSQL&& postgreSQL)  noexcept :session_{std::move(postgreSQL.session_)}, configuration_{std::move(postgreSQL.configuration_)}
{
}

auto PostgreSQL::operator=(PostgreSQL&& postgreSQL)  noexcept -> PostgreSQL&
{
    session_ = std::move(postgreSQL.session_);
    configuration_ = std::move(postgreSQL.configuration_);
    return *this;
}

PostgreSQL::~PostgreSQL()
{
    closeConnection();
}

auto PostgreSQL::connect() -> bool
{
    if(session_->is_connected())
    {
        INFO_LOG("Connection is ongoing");
        return true;
    }
    return false;
}

auto PostgreSQL::isConnected() -> bool
{
return false;
}

auto PostgreSQL::reconnect() -> bool
{
return false;
}

auto PostgreSQL::disconnect() -> bool
{
    return closeConnection();
}

auto PostgreSQL::closeConnection() -> bool
{
    return false;
}
} // namespace toad::storage::database::postgresql
