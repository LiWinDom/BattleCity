#include "ITank.h"

ITank::ITank(ObjectType type, const sf::Vector2f& position) : IObject(type, position, sf::Vector2f(16, 16)) {}

uint8_t ITank::getState() const {
  return _wheelState << 2 | _rotation;
}

void ITank::snap(float& cordinate) {
  if ((int)cordinate % 8 > 4) cordinate += 8;
  cordinate -= (int)cordinate % 8;
}
