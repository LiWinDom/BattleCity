#include <map>

#include "Other/Log.h"
#include "Game/Render/Window.h"

#include "Game/Objects/PlayerTank.h"
#include "Game/Objects/Block.h"
#include "Game/Objects/Border.h"
#include "Game/Objects/Bush.h"

#include "Game/Render/Drawables/TankDrawable.h"
#include "Game/Render/Drawables/BlockDrawable.h"
#include "Game/Render/Drawables/BushDrawable.h"

int main(int argc, char* argv[]) {
  Log::message("Started client");
  Log::message(std::string("Version: ") + CLIENT_VERSION);
  Log::message("");

  try {
    sf::Clock globalClock;
    auto window = std::make_unique<Window>();

    std::vector<std::shared_ptr<IObject>> objects;
    std::map<uint16_t, std::shared_ptr<IDrawable>> drawables;

    objects.push_back(std::make_shared<Border>(0));
    objects.push_back(std::make_shared<Border>(1));
    objects.push_back(std::make_shared<Border>(2));
    objects.push_back(std::make_shared<Border>(3));

    objects.push_back(std::make_shared<Block>(sf::Vector2f(40, 16)));
    objects.push_back(std::make_shared<Block>(sf::Vector2f(16, 40)));
    objects.push_back(std::make_shared<Block>(sf::Vector2f(40, 40)));

    objects.push_back(std::make_shared<PlayerTank>(sf::Vector2f(0, 0)));

    objects.push_back(std::make_shared<Block>(sf::Vector2f(16, 16)));
    objects.push_back(std::make_shared<Block>(sf::Vector2f(40, 16)));
    objects.push_back(std::make_shared<Block>(sf::Vector2f(16, 40)));
    objects.push_back(std::make_shared<Block>(sf::Vector2f(40, 40)));

    objects.push_back(std::make_shared<Bush>(sf::Vector2f(24, 24)));
    objects.push_back(std::make_shared<Bush>(sf::Vector2f(32, 24)));
    objects.push_back(std::make_shared<Bush>(sf::Vector2f(24, 32)));
    objects.push_back(std::make_shared<Bush>(sf::Vector2f(32, 32)));

    while (window->isOpen()) {
      window->clear();

      for (size_t i = 0; i < objects.size(); ++i) {
        const auto object = objects[i];
        if (object->isDestroyed()) {
          drawables.erase(object->getId());
          objects.erase(objects.begin() + i);
          --i;
          continue;
        }

        if (!drawables.contains(object->getId())) {
          switch (object->getType()) {
            case ObjectType::PlayerTank:
            case ObjectType::EnemyTank:
              drawables[object->getId()] = std::make_shared<TankDrawable>();
              break;
            case ObjectType::Block:
            case ObjectType::Border:
              drawables[object->getId()] = std::make_shared<BlockDrawable>();
              break;
            case ObjectType::Bush:
              drawables[object->getId()] = std::make_shared<BushDrawable>();
              break;
          }
        }
        drawables[object->getId()]->update(object);
        window->draw(*drawables[object->getId()]);
      }
      window->display();

      auto event = window->pollEvent();
      for (size_t i = 0; i < objects.size(); ++i) {
        objects[i]->think(objects, i, globalClock, event);
      }
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