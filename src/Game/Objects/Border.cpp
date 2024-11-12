#include "Border.h"

const sf::Vector2f positions[] = { sf::Vector2f(0, -208), sf::Vector2f(208, 0), sf::Vector2f(0, 208), sf::Vector2f(-208, 0) };

Border::Border(uint8_t borderNum) : IObject(ObjectType::Border, positions[borderNum], sf::Vector2f(208, 208)) {}

uint8_t Border::getState() const {
  return 0;
}

void Border::think(const std::vector<std::shared_ptr<IObject>> &objects, const sf::Clock &globalClock, const Event &event) {
  return;
}
