#pragma once

#include <memory>
#include <string>

#include <SFML/Network.hpp>

class ServerNetwork {
 public:
  ServerNetwork(uint16_t port);
  ~ServerNetwork();

  void send(const std::shared_ptr<uint8_t[]>& data, size_t size);
  std::vector<std::shared_ptr<uint8_t[]>> receive(size_t size);

 private:
  sf::TcpListener _listener;
  std::vector<std::unique_ptr<sf::TcpSocket>> _sockets;
};
