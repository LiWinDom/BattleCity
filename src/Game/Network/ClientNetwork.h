#pragma once

#include <memory>
#include <string>

#include <SFML/Network.hpp>

class ClientNetwork {
 public:
  ClientNetwork(const std::string& address, uint16_t port);
  ~ClientNetwork();

  void send(const std::shared_ptr<uint8_t[]>& data, size_t size);
  std::shared_ptr<uint8_t[]> receive(size_t size);

 private:
  sf::TcpSocket _socket;
};
