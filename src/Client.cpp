#include "Log.h"
#include "Render/Window.h"

#include "Game/Objects/PlayerTank.h"

int main(int argc, char* argv[]) {
  Log::message("Started client");
  Log::message(std::string("Version: ") + CLIENT_VERSION);
  Log::message("");

  try {
    auto window = new Window();

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
        }
        else {
          drawables.erase(drawables.begin() + (i--));
        }
      }
      for (const auto drawable : drawables) {
        window->draw(*drawable);
      }

      window->display();
      window->pollEvent();
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