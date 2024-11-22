#include "ITank.h"

ITank::ITank(ObjectType type, const sf::Vector2f& position) : IMovable(type, position, sf::Vector2f(16, 16), 45) {
  _collisionLayer = 1;
}

uint8_t ITank::getState() const {
  return _wheelState << 2 | (uint8_t)_rotation;
}

void ITank::snap(float& coordinate) {
  if ((int)coordinate % 8 > 4) {
    coordinate += 8;
  }
  coordinate -= (int)coordinate % 8;
}
