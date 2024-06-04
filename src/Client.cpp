#include "Log.h"
#include "Window.h"

int main(int argc, char* argv[]) {
  Log::message("Started client");
  Log::message(std::string("Version: ") + CLIENT_VERSION);
  Log::message("");

  auto window = new Window();
  IObject test(sf::Vector2f(-1, 16), sf::Vector2u(0, 0), ObjectType::Tank);
  IObject test2(sf::Vector2f(0, 0), sf::Vector2u(0, 0), ObjectType::Tank);
  IObject test3(sf::Vector2f(16, 0), sf::Vector2u(0, 0), ObjectType::Tank);
  while (window->isOpen()) {
    window->clear();
    window->draw(test);
    window->draw(test2);
    window->draw(test3);
    window->display();

    window->pollEvent();
  }

  Log::message("");
  Log::message("Terminated. Goodbye!");
  return 0;
}