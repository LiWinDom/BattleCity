#include "LeftTanks.h"

LeftTanks::LeftTanks(const uint8_t tanksNum) : IObject(ObjectType::LeftTanks, {216, 8}, {16, 80}), _state(tanksNum) {
  _collision = false;
}

uint8_t LeftTanks::getState() const {
  return _state;
}

void LeftTanks::removeTank() {
  _state -= 1;
}
