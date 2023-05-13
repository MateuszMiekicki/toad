#pragma once
#include <cstddef>
#include <string>

namespace toad::storage::database::entities
{
struct SensorData
{
    static SensorData fromJson(const std::string&);
    std::int64_t device_id{};
    std::int64_t sensor_id{};
    double value{};
    std::string table = "sensor_data";
};
} // namespace toad::storage::database::entities