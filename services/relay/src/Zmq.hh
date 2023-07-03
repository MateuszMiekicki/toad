#pragma once

#include "Message.hh"
#include "toad/services/relay/Logger.hh"
#include <atomic>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <zmq.hpp>

// std::atomic_int id{0};

class Worker
{
  public:
    int id_;

    Worker(zmq::context_t& context) : workerSocket_(context, ZMQ_DEALER)
    {
        // id_ = id++;
    }

    void work()
    {
        workerSocket_.connect("inproc://backend");

        while(true)
        {
            std::cout << "worker id " << id_;

            std::cout << "na samym poczatku\n";

            zmq::message_t identity;
            zmq::message_t request;

            workerSocket_.recv(&identity);
            workerSocket_.recv(&request);
            std::cout << "---------------\n";
            std::string id = "identity: " + std::string(static_cast<char*>(identity.data()), identity.size());
            std::string response = "request: " + std::string(static_cast<char*>(request.data()), request.size());
            std::cout << id << " " << response << std::endl;
            // Przetwarzanie żądania
            std::cout << "czekanko\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            // Odpowiedź na żądanie
            zmq::message_t replyIdentity(identity.data(), identity.size());
            zmq::message_t replyResponse(response.size());
            memcpy(replyResponse.data(), response.data(), response.size());

            workerSocket_.send(replyIdentity, ZMQ_SNDMORE);
            workerSocket_.send(replyResponse);
            std::cout << "na samym koncu\n";
        }
    }

  private:
    zmq::socket_t workerSocket_;
};

class Server
{
    MessageQueue& queue_;

  public:
    Server(MessageQueue& messageQueue) :
        queue_{messageQueue}, context_(1), frontendSocket_(context_, ZMQ_ROUTER), backendSocket_(context_, ZMQ_DEALER)
    {
    }

    void run()
    {
        frontendSocket_.bind("tcp://*:5570");
        backendSocket_.bind("inproc://backend");

        std::vector<std::thread> workerThreads;
        for(int i = 0; i < kNumWorkers; ++i)
        {
            workerThreads.emplace_back(
                [this]()
                {
                workerTask();
            });
        }

        zmq::proxy(static_cast<void*>(frontendSocket_), static_cast<void*>(backendSocket_), nullptr);

        for(auto& thread: workerThreads)
        {
            thread.join();
        }
    }

  private:
    static constexpr int kNumWorkers = 5;

    zmq::context_t context_;
    zmq::socket_t frontendSocket_;
    zmq::socket_t backendSocket_;

    void workerTask()
    {
        Worker worker(context_);
        worker.work();
    }
};
