#include <map>

#include "Other/Log.h"
#include "Game/Network/ServerNetwork.h"
#include "Game/Network/Serializer.h"
#include "Game/Game.h"

int main(int argc, char* argv[]) {
  Log::message("Started server");
  Log::message(std::string("Version: ") + SERVER_VERSION);
  Log::message("");
  std::cout.setf(std::ios::unitbuf);

  try {
    ServerNetwork server(61000);
    auto game = std::make_unique<Game>(0, true);

    std::map<uint8_t, std::shared_ptr<uint8_t[]>> prevBytes;
    while (true) {
      for (const auto object : game->getObjects()) {
        // Some send optimisation
        auto bytes = Serializer::objectToBytes(object);

        bool needSend = false;
        if (prevBytes.count(object->getId()) <= 0) {
          prevBytes[object->getId()] = bytes;
          needSend = true;
        }
        else {
          for (auto i = 0; i < Serializer::getObjectSize(); ++i) {
            if (prevBytes[object->getId()][i] != bytes[i]) {
              needSend = true;
              break;
            }
          }
        }

        if (needSend) {
          server.send(bytes, Serializer::getObjectSize());
        }
        if (object->isDestroyed()) {
          prevBytes.erase(object->getId());
        }
        else {
          prevBytes[object->getId()] = bytes;
        }
      }
      // End of objects
      server.send(Serializer::objectToBytes(std::make_shared<IObject>(ObjectType::NetworkTerminator, sf::Vector2f(0, 0), sf::Vector2f(0, 0))), Serializer::getObjectSize());

      auto eventData = server.receive(1);
      auto event = Serializer::bytesToEvent(eventData[0], eventData[1]);

      game->think(event);
      if (game->isFinished() || event.player1.reset || event.player2.reset) {
        if (game->isFinished()) {
          game = std::make_unique<Game>(game.get());
          server.send(Serializer::objectToBytes(std::make_shared<IObject>(ObjectType::NewStage, sf::Vector2f(0, 0), sf::Vector2f(0, 0))), Serializer::getObjectSize());
        }
        else if (event.player1.reset) {
          game = std::make_unique<Game>(0, false);
          server.send(Serializer::objectToBytes(std::make_shared<IObject>(ObjectType::NewStage, sf::Vector2f(0, 0), sf::Vector2f(0, 0))), Serializer::getObjectSize());
        }
      }
    }
  }
  catch (const std::runtime_error& error) {
    Log::message("");
    Log::error("Something critical went wrong :(");
    Log::error(error.what());
  }

  Log::message("");
  Log::message("Terminated. Goodbye!");
  return 0;
}
