#include "ClientNetwork.h"

#include <iomanip>
#include <sstream>

#include <fmt/format.h>

#include "../../Other/Log.h"

ClientNetwork::ClientNetwork(const std::string &address, uint16_t port) {
    if (_socket.connect(address, port) != sf::Socket::Done) {
      throw std::runtime_error(fmt::format("Failed to connect to {}:{} (is the server running?)", address, port));
    }
    Log::info(fmt::format("Connected to {}:{}", address, port));
}

ClientNetwork::~ClientNetwork() {
  _socket.disconnect();
  Log::info("Client disconnected");
}

void ClientNetwork::send(const std::shared_ptr<uint8_t[]>& data, size_t size) {
  if (_socket.send(data.get(), size) != sf::Socket::Status::Done) {
    // Data to string
    std::ostringstream stringData;
    for (auto i = 0; i < size; ++i) {
      stringData << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << (int)data[i] << ' ';
    }

    throw std::runtime_error(fmt::format("Failed to send data\nSize: {}\nData: {}", size, stringData.str()));
  }
}

std::shared_ptr<uint8_t[]> ClientNetwork::receive(size_t size) {
  std::shared_ptr<uint8_t[]> data(new uint8_t[size], std::default_delete<uint8_t[]>());

  sf::Socket::Status status;
  size_t totalReceived = 0;

  do {
    size_t received;
    status = _socket.receive(data.get() + totalReceived, size - totalReceived, received);
    totalReceived += received;

    if (status == sf::Socket::Error) {
      throw std::runtime_error("Failed to get data from server");
    }
    if (status == sf::Socket::Disconnected) {
      throw std::runtime_error("Server disconnected");
    }
  } while (status == sf::Socket::Partial);

  return data;
}
