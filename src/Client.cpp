#include "Log.h"
#include "Game/Render/Window.h"

#include "Game/Objects/PlayerTank.h"

int main(int argc, char* argv[]) {
  Log::message("Started client");
  Log::message(std::string("Version: ") + CLIENT_VERSION);
  Log::message("");

  try {
    sf::Clock globalClock;
    auto window = std::make_unique<Window>();

    std::vector<std::shared_ptr<IObject>> objects;
    std::vector<std::shared_ptr<Drawable>> drawables;
    objects.push_back(std::make_shared<PlayerTank>(sf::Vector2f(0, 0)));

    while (window->isOpen()) {
      window->clear();
      for (size_t i = 0; i < std::max(objects.size(), drawables.size()); ++i) {
        if (i < objects.size()) {
          if (i < drawables.size()) {
            drawables[i]->update(*objects[i]);
          }
          else {
            drawables.emplace_back(std::make_shared<Drawable>(*objects[i]));
          }
          window->draw(*drawables[i]);
        }
        else {
          drawables.erase(drawables.begin() + (i--));
        }
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