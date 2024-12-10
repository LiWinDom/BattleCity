#include <map>

#include "Other/Log.h"

#include "Game/Game.h"

#include "Game/Render/Window.h"
#include "Game/Render/Drawables/TankDrawable.h"
#include "Game/Render/Drawables/WallDrawable.h"
#include "Game/Render/Drawables/BrickDrawable.h"
#include "Game/Render/Drawables/BorderDrawable.h"
#include "Game/Render/Drawables/BulletDrawable.h"
#include "Game/Render/Drawables/BushDrawable.h"
#include "Game/Render/Drawables/ExplosionDrawable.h"

int main(int argc, char* argv[]) {
  Log::message("Started client");
  Log::message(std::string("Version: ") + CLIENT_VERSION);
  Log::message("");

  try {
    auto window = std::make_unique<Window>();
    const std::vector<std::string> field = {
        "s           s           s ",
        "                          ",
        "  bb  bb  bb  bb  bb  bb  ",
        "  bb  bb  bb  bb  bb  bb  ",
        "  bb  bb  bb  bb  bb  bb  ",
        "  bb  bb  bb  bb  bb  bb  ",
        "  bb  bb  bbwwbb  bb  bb  ",
        "  bb  bb  bbwwbb  bb  bb  ",
        "  bb  bb  bb  bb  bb  bb  ",
        "  bb  bb          bb  bb  ",
        "  bb  bb          bb  bb  ",
        "          bb  bb          ",
        "          bb  bb          ",
        "bb  bbbb          bbbb  bb",
        "ww  bbbb          bbbb  ww",
        "          bb  bb          ",
        "          bbbbbb          ",
        "  bb  bb  bbbbbb  bb  bb  ",
        "  bb  bb  bb  bb  bb  bb  ",
        "  bb  bb  bb  bb  bb  bb  ",
        "  bb  bb  bb  bb  bb  bb  ",
        "  bb  bb          bb  bb  ",
        "  bb  bb          bb  bb  ",
        "  bb  bb   pppp   bb  bb  ",
        "        1  pe p 2         ",
        "           p  p           ",
    };
    Game game(field, {});
    std::map<uint16_t, std::shared_ptr<IDrawable>> drawables;

    while (window->isOpen()) {
      window->clear();

      for (const auto object : game.getObjects()) {
        if (object->isDestroyed()) {
          drawables.erase(object->getId());
          continue;
        }

        if (!drawables.contains(object->getId())) {
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
            case ObjectType::Explosion:
              drawables[object->getId()] = std::make_shared<ExplosionDrawable>();
              break;
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
  catch (...) {
    Log::message("");
    Log::error("Something critical went wrong :(");
    Log::error("...and we don't know what is it");
  }

  Log::message("");
  Log::message("Terminated. Goodbye!");
  return 0;
}