#include "ITank.h"

ITank::ITank(ObjectType type, const sf::Vector2f& position) : IObject(type, position, sf::Vector2f(16, 16)) {
  _speed = 45;
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
