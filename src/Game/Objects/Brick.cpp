#include "Brick.h"

Brick::Brick(const sf::Vector2f& position) : IBlock(ObjectType::Brick, position) {}

uint8_t Brick::getState() const {
  return _state;
}

void Brick::think(std::vector<std::shared_ptr<IObject>> &objects, const sf::Clock &globalClock, const Event &event) {
  return;
}
