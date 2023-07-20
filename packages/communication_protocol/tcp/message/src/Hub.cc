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
    cond_.wait(lock,
               [this]
               {
        return !queue_.empty();
    });
    auto message = queue_.front();
    queue_.pop();
    return message;
}

void Hub::printAllMessages()
{
    std::unique_lock<std::mutex> lock(mutex_);
    if(!queue_.empty())
    {
        INFO_LOG("Printing top message");
        auto message = queue_.front();
        TRACE_LOG("Message: {}", message.id_.id);
    }
}

} // namespace toad::communication_protocol::tcp