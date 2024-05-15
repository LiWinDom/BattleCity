#include "Game.h"
#include "Log.h"
#include "Window.h"

int main() {
  Log::message("Started client");
  Log::message(std::string("Version: ") + CLIENT_VERSION);
  Log::message("");

  auto window = new Window();
  while (window->isOpen()) {
    window->clear();
    window->display();

    window->pollEvent();
  }

  Log::message("");
  Log::message("Terminated. Goodbye!");
  return 0;
}