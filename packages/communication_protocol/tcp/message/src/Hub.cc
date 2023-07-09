#include "toad/communication_protocol/tcp/message/Hub.hh"
#include "toad/communication_protocol/tcp/Logger.hh"

namespace toad::communication_protocol::tcp
{
void Hub::push(const Message &message)
{
    std::unique_lock<std::mutex> lock(mutex_);
    queue_.push(message);
    cond_.notify_one();
}

Message Hub::pop()
{
    std::unique_lock<std::mutex> lock(mutex_);
    cond_.wait(lock, [this] { return !queue_.empty(); });
    auto message = queue_.front();
    queue_.pop();
    return message;
}

void Hub::printAllMessages()
{
    INFO_LOG("Printing all messages");
    std::unique_lock<std::mutex> lock(mutex_);
    while (!queue_.empty())
    {
        auto message = queue_.front();
        queue_.pop();
        TRACE_LOG("Message: {}", message.id_.id);
    }
}
}