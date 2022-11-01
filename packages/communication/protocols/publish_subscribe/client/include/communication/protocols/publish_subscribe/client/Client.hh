#pragma once
#include <communication/protocols/publish_subscribe/interface/Client.hh>
#include <communication/protocols/publish_subscribe/publisher/interface/Publisher.hh>
#include <communication/protocols/types/server_details/ServerDetails.hh>

namespace toad::communication::protocols::publish_subscribe
{
class Client : public interface::Publisher, public interface::Client
{
  private:
    types::ServerDetails serverDetails_;

  public:
    explicit Client(const types::ServerDetails&);
    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;
    Client(Client&&);
    Client& operator=(Client&);

    bool connect() override;
    bool disconnect() override;
    bool reestablishConnection() override;
    void publish() override;
    ~Client();
};
} // namespace toad::communication::protocols::publish_subscribe