#pragma once
#include "servertcp.hh"
#include "toad/services/relay/Logger.hh"
#include "Zmq.hh"
#include <atomic>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>
#include <zmq.hpp>

struct Message
{
    enum class Type
    {
        undefined,
        request,
        push
    };
    using clientIdentifier_t = std::string;
    using content_t = std::string;

    Type type_;
    clientIdentifier_t sender_;
    clientIdentifier_t receiver_;
    content_t content_;

    Message(Type type, clientIdentifier_t sender, clientIdentifier_t receiver, content_t content) :
        type_(type), sender_(sender), receiver_(receiver), content_(content)
    {
    }

    Message(const Message&) = default;
    Message(Message&&) = default;
    Message& operator=(const Message&) = default;
    Message& operator=(Message&&) = default;
    ~Message() = default;
};

class MessageQueue
{
    std::queue<Message> queue_;
    std::mutex mutex_;

  public:
    MessageQueue() = default;
    MessageQueue(MessageQueue&&) = default;
    MessageQueue& operator=(MessageQueue&&) = default;
    ~MessageQueue() = default;

    void push(Message&& message)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(std::move(message));
    }

    Message pop()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        auto message = std::move(queue_.front());
        queue_.pop();
        return message;
    }
};

class MessageExecutor
{
    MessageQueue& messageQueue_;
    Server& zmqServer_;

  public:
    MessageExecutor(MessageQueue& messageQueue, Server& zmq) : messageQueue_(messageQueue), zmqServer_(zmq)
    {
    }

    void run()
    {
        while(true)
        {
            auto message = messageQueue_.pop();
            std::thread messageThread(
                [this, message]()
                {
                execute(message);
            });
            messageThread.detach();
        }
    }

    void execute(Message message)
    {
        switch(message.type_)
        {
            case Message::Type::request:
                // tcpServer_.send(message.request_, message.clientIdentifier_);

                // auto result = timer(tcpServer_.receive(), 1s);
                // if (result)
                //     zmqServerReqResp_.send(result, message.clientIdentifier_);
                // zmqServerReqResp_.send(Message::Cause::Timeout, message.clientIdentifier_);
                break;
            case Message::Type::push:
                // zmqServerPushPull_.send(message.message_, message.clientIdentifier_);
                break;
            case Message::Type::undefined:
                break;
        }
    }
};