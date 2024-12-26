#include "NetworkObject.h"

NetworkObject::NetworkObject(uint16_t id, ObjectType type, bool destroyed, uint8_t posX, uint8_t posY, uint8_t state) :
IObject(type, {(float)posX, (float)posY}, {0, 0}), _state(state) {
  _id = id;
  _desytroyed = destroyed;
}

uint8_t NetworkObject::getState() const {
  return _state;
}
