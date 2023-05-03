#pragma once
#include <cstddef>
#include <string>

namespace toad::storage::database::model
{
struct SensorData
{
    std::int64_t device_id;
    std::int64_t sensord_id;
    double value;
    std::string table = "sensor_data";
};
} // namespace toad::storage::database::model