#include <fstream>
#include <map>

#include <SFML/Network.hpp>

#include "Other/Log.h"
#include "Game/Objects/NetworkObject.h"
#include "Game/Render/Drawables.h"
#include "Game/Render/Window.h"

int main(int argc, char* argv[]) {
  Log::message("Started client");
  Log::message(std::string("Version: ") + CLIENT_VERSION);
  Log::message("");
  std::cout.setf(std::ios::unitbuf);

  std::shared_ptr<Game> game = nullptr;
  sf::TcpSocket server;

  try {
    std::ifstream configFile(Path::getAbsolutePath("client.config"));

    if (!configFile.is_open()) {
      Log::info("Config file not found, starting local game");
      game = std::make_shared<Game>(1, false);
    }
    else {
      std::string address;
      configFile >> address;
      configFile.close();

      auto status = server.connect(address, 61000);
      if (status != sf::Socket::Done) {
        throw std::runtime_error("Failed to connect to server (is it running?)");
      }
    }

    auto window = std::make_unique<Window>();
    std::map<uint16_t, std::shared_ptr<IDrawable>> drawables;

    while (window->isOpen()) {
      window->clear();

      size_t objectsNum;
      if (game == nullptr) {
        uint8_t objectSizeData[2];
        std::size_t received;
        if (server.receive(objectSizeData, 2, received) != sf::Socket::Done) {
          throw std::runtime_error("Failed to get data from server");
        }
        objectsNum = ((uint16_t)objectSizeData[0]) << 8 | objectSizeData[1];
      }
      else {
        objectsNum = game->getObjects().size();
      }

      const size_t objectSize = 7;
      std::vector<std::shared_ptr<IObject>> objects;

      if (game == nullptr) {
        // [id][id][ObjectType][destroyed][posX][posY][state]
        uint8_t objectsData[16384];
        std::size_t received;
        if (server.receive(objectsData, objectsNum * objectSize, received) != sf::Socket::Done) {
          throw std::runtime_error("Failed to get data from server");
        }

        for (auto i = 0; i < objectsNum; ++i) {
          objects.push_back(std::make_shared<NetworkObject>(
              (uint16_t)objectsData[i * objectSize + 0] << 8 | objectsData[i * objectSize + 1],
              static_cast<ObjectType>(objectsData[i * objectSize + 2]),
              objectsData[i * objectSize + 3],
              objectsData[i * objectSize + 4],
              objectsData[i * objectSize + 5],
              objectsData[i * objectSize + 6]
              ));
        }
      }
      else {
        objects = game->getObjects();
      }

      for (const auto object : objects) {
        if (object->isDestroyed()) {
          drawables.erase(object->getId());
          continue;
        }

        if (drawables.count(object->getId()) <= 0) {
          switch (object->getType()) {
            case ObjectType::PlayerTank:
            case ObjectType::EnemyTank:
              drawables[object->getId()] = std::make_shared<TankDrawable>();
              break;
            case ObjectType::Brick:
              drawables[object->getId()] = std::make_shared<BrickDrawable>();
              break;
            case ObjectType::Wall:
              drawables[object->getId()] = std::make_shared<WallDrawable>();
              break;
            case ObjectType::Border:
              drawables[object->getId()] = std::make_shared<BorderDrawable>();
              break;
            case ObjectType::Bullet:
              drawables[object->getId()] = std::make_shared<BulletDrawable>();
              break;
            case ObjectType::Bush:
              drawables[object->getId()] = std::make_shared<BushDrawable>();
              break;
            case ObjectType::Eagle:
              drawables[object->getId()] = std::make_shared<EagleDrawable>();
              break;
            case ObjectType::Explosion:
              drawables[object->getId()] = std::make_shared<ExplosionDrawable>();
              break;
            case ObjectType::Spawner:
              drawables[object->getId()] = std::make_shared<TankSpawnerDrawable>();
              break;
            case ObjectType::GameOver:
              drawables[object->getId()] = std::make_shared<GameOverDrawable>();
              break;
            default:
              Log::warning("No drawable assigned to object");
              continue;
          }
        }
        drawables[object->getId()]->update(object);
      }

      // Render objects
      std::vector<std::shared_ptr<IDrawable>> drawablesPointers;
      drawablesPointers.reserve(drawables.size());
      for (const auto& drawable : drawables) {
        drawablesPointers.push_back(drawable.second);
      }
      // Sorting by layers
      std::sort(drawablesPointers.begin(), drawablesPointers.end(), [](const std::shared_ptr<IDrawable>& a, const std::shared_ptr<IDrawable>& b) -> bool {
        return a->getLayer() < b->getLayer();
      });
      for (const auto& drawable : drawablesPointers) {
        window->draw(*drawable);
      }
      window->display();

      auto event = window->pollEvent();

      if (game == nullptr) {
        // [esc][][][up][left][down][right][shoot]
        uint8_t pressed = (event.player1.esc | event.player2.esc) << 8
                          | (event.player1.up | event.player2.up) << 4
                          | (event.player1.left | event.player2.left) << 3
                          | (event.player1.down | event.player2.down) << 2
                          | (event.player1.right | event.player2.right) << 1
                          | (event.player1.shoot | event.player2.shoot);
        uint8_t sendData[] = {pressed};

        if (server.send(sendData, 1) != sf::Socket::Done) {
          throw std::runtime_error("Failed to send data to player 1");
        }
      }
      else {
        game->think(event);
      }
    }
  }
  catch (const std::runtime_error& error) {
    Log::message("");
    Log::error("Something critical went wrong :(");
    Log::error(error.what());
  }

  server.disconnect();
  Log::message("");
  Log::message("Terminated. Goodbye!");
  return 0;
}
