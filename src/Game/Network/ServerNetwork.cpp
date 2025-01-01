#include "ServerNetwork.h"

#include <iomanip>
#include <sstream>

#include <fmt/format.h>

#include "../../Other/Log.h"

ServerNetwork::ServerNetwork(uint16_t port) {
  _listener.listen(port);
  // Waiting for 2 connections
  _sockets.resize(2);
  for (auto& socket : _sockets) {
    socket = std::make_unique<sf::TcpSocket>();
  }

  if (_listener.accept(*_sockets[0]) != sf::Socket::Done) {
    throw std::runtime_error("Failed to accept connection from player 1");
  }
  Log::info(fmt::format("Player 1 connected from {}:{}", _sockets[0]->getRemoteAddress().toString(), _sockets[0]->getRemotePort()));
  if (_listener.accept(*_sockets[1]) != sf::Socket::Done) {
    throw std::runtime_error("Failed to accept connection from player 2");
  }
  Log::info(fmt::format("Player 2 connected from {}:{}", _sockets[1]->getRemoteAddress().toString(), _sockets[1]->getRemotePort()));
}

ServerNetwork::~ServerNetwork() {
  _listener.close();
  for (auto &socket : _sockets) {
    socket->disconnect();
  }
  Log::info("Server closed");
}

void ServerNetwork::send(const std::unique_ptr<uint8_t[]>& data, size_t size) {
  for (auto& socket : _sockets) {
    if (socket->send(data.get(), size) != sf::Socket::Status::Done) {
      // Data to string
      std::ostringstream stringData;
      for (auto i = 0; i < size; ++i) {
        stringData << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << (int)data.get()[i] << ' ';
      }

      throw std::runtime_error(fmt::format("Failed to send data\nSize: {}\nData: {}", size, stringData.str()));
    }
  }
}

std::vector<std::unique_ptr<uint8_t[]>> ServerNetwork::receive(size_t size) {
  std::vector<std::unique_ptr<uint8_t[]>> data(_sockets.size());
  for (auto& d : data) {
    d = std::make_unique<uint8_t[]>(size);
  }

  for (auto i = 0; i < _sockets.size(); ++i) {
    auto& socket = _sockets[i];

    sf::Socket::Status status;
    size_t totalReceived = 0;

    do {
      size_t received;
      status = socket->receive(data[i].get() + totalReceived, size - totalReceived, received);
      totalReceived += received;

      if (status == sf::Socket::Error) {
        throw std::runtime_error(fmt::format("Failed to get data from client {}", i));
      }
      if (status == sf::Socket::Disconnected) {
        throw std::runtime_error(fmt::format("Client {} disconnected", i));
      }
    } while (status == sf::Socket::Partial);
  }

  return data;
}
