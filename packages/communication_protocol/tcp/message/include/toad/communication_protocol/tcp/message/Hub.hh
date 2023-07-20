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
        std::thread t(
            [this]()
            {
            while(true)
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

// class Task
// {
//   private:
//     const Message message_;
//   public:
//     Task(const Message &message) : message_{message} {}
//     void work();
// };

// class Dispatcher
// {
//   private:
//     Hub &incoming_;
//     Hub outgoing_;

//   public:
//     Dispatcher(Hub &incoming) : incoming_{incoming} {}
//     void dispatch();
//     {
//         while (true)
//         {
//             std::thread t([this]() {
//                 auto message = incoming_.pop();
//                 Task task(message);
//                 auto msg = task.work();
//                 outgoing_.push(msg);
//             });
//             t.detach();
//         }
//     }
// };
} // namespace toad::communication_protocol::tcp