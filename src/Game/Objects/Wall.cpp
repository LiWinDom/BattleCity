#include "Wall.h"

Wall::Wall(const sf::Vector2f& position) : IBlock(ObjectType::Block, position) {}

uint8_t Wall::getState() const {
  return 0;
}

void Wall::think(std::vector<std::shared_ptr<IObject>> &objects, const sf::Clock &globalClock, const Event &event) {
  return;
}
