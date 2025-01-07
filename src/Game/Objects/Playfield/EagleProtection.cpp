#include "EagleProtection.h"

EagleProtection::EagleProtection(const sf::Vector2f& position) : Brick(position), Wall(position), IBlock(ObjectType::EagleProtection, position) {}

uint8_t EagleProtection::getState() const {
  return _protectionState << 4 | Brick::getState();
}

void EagleProtection::addProtection(Game& game, float time) {
  time = time / 60 * 64;
  _stateUntil = game.getTime() + time;
  _protectionState = 2;
  _state = 15;
}

void EagleProtection::removeProtection(Game& game, float time) {
  time = time / 60 * 64;
  _stateUntil = game.getTime() + time;
  _protectionState = 0;
  _collision = false;
}

void EagleProtection::think(Game &game, const Event &event) {
  if (_stateUntil < game.getTime()) {
    _protectionState = 1;
    _collision = true;
  }
}

void EagleProtection::destroy(Game& game, const ObjectRotation& bulletRotation) {
  if (_protectionState == 1) {
    Brick::destroy(game, bulletRotation);
    _desytroyed = false;
  }
  else if (_protectionState == 2) {
    Wall::destroy(game, bulletRotation);
  }
}
