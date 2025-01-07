#include "TankProtection.h"

TankProtection::TankProtection(IObject* tank, float protectionUntil) :
  IObject(ObjectType::TankProtection, tank->getPosition(), {16, 16}), _tankPointer(tank), _protectionUntil(protectionUntil) {}

uint8_t TankProtection::getState() const {
  return _state;
}

void TankProtection::think(Game &game, const Event &event) {
  if (game.getTime() > _protectionUntil || _tankPointer == nullptr || _tankPointer->isDestroyed()) {
    _desytroyed = true;
    _tankPointer = nullptr;
    return;
  }
  _position = _tankPointer->getPosition();
  _state = (int)(game.getTime() * 20) % 2;
}
