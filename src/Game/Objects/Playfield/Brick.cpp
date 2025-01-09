#include "Brick.h"

Brick::Brick(const sf::Vector2f& position) : IBlock(ObjectType::Brick, position) {}

uint8_t Brick::getState() const {
  return _state;
}

void Brick::destroy(Game& game, const ObjectRotation& bulletRotation, const bool powerfulBullet) {
  if (powerfulBullet) {
    _state = 0;
  }
  else {
    switch (bulletRotation) {
      case ObjectRotation::Up:
        if (_state & 0b1100) {
          _state = _state & 0b0011;
        } else {
          _state = _state & 0b1100;
        }
        break;
      case ObjectRotation::Left:
        if (_state & 0b1010) {
          _state = _state & 0b0101;
        } else {
          _state = _state & 0b1010;
        }
        break;
      case ObjectRotation::Down:
        if (_state & 0b0011) {
          _state = _state & 0b1100;
        } else {
          _state = _state & 0b0011;
        }
        break;
      case ObjectRotation::Right:
        if (_state & 0b0101) {
          _state = _state & 0b1010;
        } else {
          _state = _state & 0b0101;
        }
        break;
    }
  }
  
  if (_state == 0) {
    _desytroyed = true;
  }
}
