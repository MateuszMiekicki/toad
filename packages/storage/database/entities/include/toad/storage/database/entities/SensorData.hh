#pragma once
#include <cstddef>
#include <string>
#include <vector>

namespace toad::storage::database::entities
{
struct SensorData
{
    std::int64_t device_id{};
    std::int64_t sensor_id{};
    double value{};
    const std::string table = "sensor_data";
};

using sensorDatalist_t = std::vector<SensorData>;
} // namespace toad::storage::database::entities