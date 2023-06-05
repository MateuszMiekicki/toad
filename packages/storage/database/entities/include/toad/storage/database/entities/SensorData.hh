#pragma once
#include <cstddef>
#include <string>
#include <vector>

namespace toad::storage::database::entities
{
struct SensorData
{
    std::string mac_address{};
    std::int64_t pin_number{};
    double value{};
    const std::string table = "sensor_data";
};

using sensorDatalist_t = std::vector<SensorData>;
} // namespace toad::storage::database::entities