#include "Bush.h"

Bush::Bush(const sf::Vector2f& position) : IBlock(ObjectType::Bush, position) {
  _collision = false;
}

uint8_t Bush::getState() const {
  return 0;
}

void Bush::think(std::vector<std::shared_ptr<IObject>> &objects, const sf::Clock &globalClock, const Event &event) {
  return;
}
