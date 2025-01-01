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
    Game game(0, true);

    while (true) {
      for (const auto object : game.getObjects()) {
        server.send(Serializer::objectToBytes(object), Serializer::getObjectSize());
      }
      // End of objects
      server.send(Serializer::objectToBytes(std::make_shared<IObject>(ObjectType::NetworkTerminator, sf::Vector2f(0, 0), sf::Vector2f(0, 0))), Serializer::getObjectSize());

      auto eventData = server.receive(1);
      auto event = Serializer::bytesToEvent(eventData[0], eventData[1]);

      game.think(event);
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
