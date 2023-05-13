#pragma once
#include "toad/storage/database/entities/SensorData.hh"
#include <memory>
#include <questdb/ilp/line_sender.hpp>
#include <string>

namespace toad::storage::database
{
class QuestDB
{
  private:
    std::unique_ptr<questdb::ilp::line_sender> sender_{nullptr};
    std::unique_ptr<questdb::ilp::line_sender_buffer> buffer_{nullptr};

  public:
    QuestDB(const QuestDB&) = delete;
    QuestDB& operator=(const QuestDB&) = delete;

    QuestDB(const std::string&, const std::string&);
    void insert(const entities::SensorData&);
    void commit();
    void rollback();
};
} // namespace toad::storage::database