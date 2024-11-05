#include "Block.h"

Block::Block(const sf::Vector2f& position) : IBlock(ObjectType::Block, position) {}

uint8_t Block::getState() const {
  return 0;
}

void Block::think(const std::vector<std::shared_ptr<IObject>> &objects, uint16_t index, const sf::Clock &globalClock, const Event &event) {
  return;
}
