#pragma once
#include "toad/communication_protocol/tcp/dispatcher/interface/Dispatcher.hh"
#include "toad/communication_protocol/tcp/interface/Sender.hh"
#include "toad/communication_protocol/tcp/message/Hub.hh"

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
