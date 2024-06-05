#include "Log.h"
#include "Window.h"

#include "Objects/ITank.h"

int main(int argc, char* argv[]) {
  Log::message("Started client");
  Log::message(std::string("Version: ") + CLIENT_VERSION);
  Log::message("");

  try {
    auto window = new Window();
    while (window->isOpen()) {
      auto tank = ITank(sf::Vector2i(0, 0));
      window->clear();
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