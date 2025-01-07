#include "Eagle.h"

Eagle::Eagle(const sf::Vector2f& position) : IObject(ObjectType::Eagle, position, {16, 16}) {}

uint8_t Eagle::getState() const {
  return _state;
}

void Eagle::destroy(Game &game, const ObjectRotation& bulletRotation) {
  _state = true;
}
