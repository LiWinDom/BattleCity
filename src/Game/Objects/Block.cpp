#include "Block.h"

Block::Block(const sf::Vector2f& position) : IBlock(ObjectType::Block, position) {}

uint8_t Block::getState() const {
  return 0;
}

void Block::think(std::vector<std::shared_ptr<IObject>> &objects, const sf::Clock &globalClock, const Event &event) {
  return;
}
