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
    virtual ~Hub() = default;

    virtual void push(const Message &);
    virtual Message pop();
};
} // namespace toad::communication_protocol::tcp