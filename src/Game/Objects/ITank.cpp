#include "ITank.h"

ITank::ITank(ObjectType type, const sf::Vector2f& position) : IObject(type, position, sf::Vector2f(16, 16)) {}

uint16_t ITank::getState() const {
  return 0;
}
