#include "toad/storage/database/questdb/QuestDB.hh"

namespace toad::storage::database
{
QuestDB::QuestDB(const std::string& address, const std::string& port) :
    sender_(std::make_unique<questdb::ilp::line_sender>(questdb::ilp::opts{address, port})),
    buffer_{std::make_unique<questdb::ilp::line_sender_buffer>()}
{
}

void QuestDB::insert(const model::SensorData& sensorData)
{
    buffer_->table(sensorData.table)
        .column("device_id", sensorData.device_id)
        .column("sensor_id", sensorData.sensor_id)
        .column("value", sensorData.value)
        .at_now();
}

void QuestDB::commit()
{
    sender_->flush(*buffer_);
}

void QuestDB::rollback()
{
}
} // namespace toad::storage::database