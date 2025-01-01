#include "Water.h"

Water::Water(const sf::Vector2f& position) : IBlock(ObjectType::Water, position) {}

uint8_t Water::getState() const {
  return _currentFrame;
}

void Water::think(Game &game, const Event &event) {
  _currentFrame = (int)(game.getTime() * 2) % 2 + 1;
}
