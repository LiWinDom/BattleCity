#include <map>

#include "Other/Log.h"
#include "Game/Network/ClientNetwork.h"
#include "Game/Network/Serializer.h"
#include "Game/Render/Drawables.h"
#include "Game/Render/Window.h"

int main(int argc, char* argv[]) {
  Log::message("Started client");
  Log::message(std::string("Version: ") + CLIENT_VERSION);
  Log::message("");
  std::cout.setf(std::ios::unitbuf);

  std::unique_ptr<Game> game = nullptr;
  std::unique_ptr<ClientNetwork> client = nullptr;

  try {
    std::ifstream configFile(Path::getAbsolutePath("client.config"));

    if (!configFile.is_open()) {
      Log::info("Config file not found, starting local game");
      game = std::make_unique<Game>(7, false);
    }
    else {
      std::string address;
      configFile >> address;
      configFile.close();

      client = make_unique<ClientNetwork>(address, 61000);
    }

    auto window = std::make_unique<Window>();
    std::map<uint32_t, std::shared_ptr<IDrawable>> drawables;

    while (window->isOpen()) {
      window->clear();

      size_t objectsNum;
      if (game == nullptr) {
        objectsNum = -1;
      }
      else {
        objectsNum = game->getObjects().size();
      }

      for (size_t i = 0; i < objectsNum; ++i) {
        // [id][id][ObjectType][destroyed][posX][posY][state]
        std::shared_ptr<IObject> object = nullptr;

        if (game == nullptr) {
          object = Serializer::bytesToObject(client->receive(Serializer::getObjectSize()));
          if (object->getType() == ObjectType::NetworkTerminator) {
            break;
          }
        }
        else {
          object = game->getObjects()[i];
        };

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
            case ObjectType::Water:
              drawables[object->getId()] = std::make_shared<WaterDrawable>();
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
        client->send(Serializer::eventToBytes(event), 1);
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

  Log::message("");
  Log::message("Terminated. Goodbye!");
  return 0;
}
