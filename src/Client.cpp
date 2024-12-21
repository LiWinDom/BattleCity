#include <map>

#include "Other/Log.h"

#include "Game/Game.h"

#include "Game/Render/Drawables.h"
#include "Game/Render/Window.h"

int main(int argc, char* argv[]) {
  Log::message("Started client");
  Log::message(std::string("Version: ") + CLIENT_VERSION);
  Log::message("");

  try {
    auto window = std::make_unique<Window>();
    Game game(1, false);
    std::map<uint16_t, std::shared_ptr<IDrawable>> drawables;

    while (window->isOpen()) {
      window->clear();

      for (const auto object : game.getObjects()) {
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
            case ObjectType::Explosion:
              drawables[object->getId()] = std::make_shared<ExplosionDrawable>();
              break;
            case ObjectType::Spawner:
              drawables[object->getId()] = std::make_shared<TankSpawnerDrawable>();
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
