#pragma once
#include "toad/communication_protocol/tcp/broker/Broker.hh"
#include "toad/communication_protocol/tcp/message/Hub.hh"
#include "toad/communication_protocol/tcp/notifier/Notifier.hh"
#include "toad/communication_protocol/tcp/requester/Requester.hh"

namespace toad::communication_protocol::tcp
{
class Dispatcher
{
  private:
    Hub& hub_;
    interface::Sender& broker_;
    interface::Sender& requester_;
    interface::Sender& notifier_;

  public:
    Dispatcher(Hub&, interface::Sender&, interface::Sender&, interface::Sender&);
    void dispatch();
};
} // namespace toad::communication_protocol::tcp
