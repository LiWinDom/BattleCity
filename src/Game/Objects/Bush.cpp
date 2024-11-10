#include "Bush.h"

Bush::Bush(const sf::Vector2f& position) : IBlock(ObjectType::Bush, position) {
  _collistion = false;
}

uint8_t Bush::getState() const {
  return 0;
}

void Bush::think(const std::vector<std::shared_ptr<IObject>> &objects, uint16_t index, const sf::Clock &globalClock, const Event &event) {
  return;
}
