#pragma once
#include "toad/communication_protocol/tcp/message/Message.hh"
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

namespace toad::communication_protocol::tcp
{
class Hub
{
  private:
    std::queue<Message> queue_{};
    std::mutex mutex_{};
    std::condition_variable cond_{};

  public:
    Hub() = default;

    void push(const Message &);
    Message pop();
};
} // namespace toad::communication_protocol::tcp