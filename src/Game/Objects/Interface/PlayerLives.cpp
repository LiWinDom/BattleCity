#include "PlayerLives.h"

PlayerLives::PlayerLives(const uint8_t playerNum) : IObject(ObjectType::PlayerLives, {224, 128}, {8, 8}) {
  if (playerNum == 1) {
    _position = {224, 152};
  }
  _collision = false;
}

uint8_t PlayerLives::getState() const {
  return _state;
}

void PlayerLives::setState(const uint8_t state) {
  _state = state;
}
