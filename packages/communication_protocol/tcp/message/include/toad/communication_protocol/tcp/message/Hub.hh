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

    void printAllMessages();
    public:
    Hub()
    {
        // print all messages every 5 seconds
        std::thread t([this]() {
            while (true)
            {
                std::this_thread::sleep_for(std::chrono::seconds(5));
                printAllMessages();
            }
        });
        t.detach();
    }
    void push(const Message &);
    Message pop();
};
} // namespace toad::communication_protocol::tcp