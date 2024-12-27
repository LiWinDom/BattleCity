#include <map>

#include <SFML/Network.hpp>

#include "Other/Log.h"
#include "Game/Game.h"
#include "Game/Objects/IObject.h"

int main(int argc, char* argv[]) {
  Log::message("Started server");
  Log::message(std::string("Version: ") + SERVER_VERSION);
  Log::message("");
  std::cout.setf(std::ios::unitbuf);

  sf::TcpListener listener;
  sf::TcpSocket player1, player2;
  try {
    // Waiting for connection of 2 players
    if (listener.listen(61000) != sf::Socket::Done) {
      throw std::runtime_error("Cannot bind to port 61000");
    }

    if (listener.accept(player1) != sf::Socket::Done) {
      throw std::runtime_error("Failed to accept connection from player");
    }
    Log::info("Player 1 connected");
    if (listener.accept(player2) != sf::Socket::Done) {
      throw std::runtime_error("Failed to accept connection from player");
    }
    Log::info("Player 2 connected");

    Game game(1, true);

    while (true) {
      auto objectsNum = game.getObjects().size();
      uint8_t objectSizeData[] = {
          (uint8_t)(objectsNum >> 8 & 255),
          (uint8_t)(objectsNum & 255),
      };
      if (player1.send(objectSizeData, 2) != sf::Socket::Done) {
        throw std::runtime_error("Failed to send data to player 1");
      }
      if (player2.send(objectSizeData, 2) != sf::Socket::Done) {
        throw std::runtime_error("Failed to send data to player 2");
      }

      const size_t objectSize = 7;
      uint8_t objectsData[16384];
      for (size_t i = 0; i < objectsNum; ++i) {
        const auto object = game.getObjects()[i];
        // [id][id][ObjectType][destroyed][posX][posY][state]
        objectsData[i * objectSize + 0] = (uint8_t)(object->getId() >> 8 & 255);
        objectsData[i * objectSize + 1] = (uint8_t)(object->getId() & 255);
        objectsData[i * objectSize + 2] = static_cast<uint8_t>(object->getType());
        objectsData[i * objectSize + 3] = (uint8_t)object->isDestroyed();
        objectsData[i * objectSize + 4] = (uint8_t)object->getPosition().x;
        objectsData[i * objectSize + 5] = (uint8_t)object->getPosition().y;
        objectsData[i * objectSize + 6] = (uint8_t)object->getState();
      }

      if (player1.send(objectsData, objectSize * objectsNum) != sf::Socket::Done) {
        throw std::runtime_error("Failed to send data to player 1");
      }
      if (player2.send(objectsData, objectSize * objectsNum) != sf::Socket::Done) {
        throw std::runtime_error("Failed to send data to player 2");
      }

      Event event;
      uint8_t pressed[1]; // [esc][][][up][left][down][right][shoot]
      std::size_t received;

      if (player1.receive(pressed, 1, received) != sf::Socket::Done) {
        throw std::runtime_error("Failed to receive pressed keys from player 1");
      }
      event.player1.esc =   (pressed[0] >> 7) & 1;
      event.player1.up =    (pressed[0] >> 4) & 1;
      event.player1.left =  (pressed[0] >> 3) & 1;
      event.player1.down =  (pressed[0] >> 2) & 1;
      event.player1.right = (pressed[0] >> 1) & 1;
      event.player1.shoot =  pressed[0] & 1;

      if (player2.receive(pressed, 1, received) != sf::Socket::Done) {
        throw std::runtime_error("Failed to receive pressed keys from player 2");
      }
      event.player2.esc =   (pressed[0] >> 7) & 1;
      event.player2.up =    (pressed[0] >> 4) & 1;
      event.player2.left =  (pressed[0] >> 3) & 1;
      event.player2.down =  (pressed[0] >> 2) & 1;
      event.player2.right = (pressed[0] >> 1) & 1;
      event.player2.shoot =  pressed[0] & 1;

      game.think(event);
    }
  }
  catch (const std::runtime_error& error) {
    Log::message("");
    Log::error("Something critical went wrong :(");
    Log::error(error.what());
  }

  listener.close();
  player1.disconnect();
  player2.disconnect();

  Log::message("");
  Log::message("Terminated. Goodbye!");
  return 0;
}
