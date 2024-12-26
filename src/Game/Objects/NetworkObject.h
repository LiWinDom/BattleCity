#pragma once

#include "IObject.h"

class NetworkObject : public IObject {
 public:
  NetworkObject(uint16_t id, ObjectType type, bool destroyed, uint8_t posX, uint8_t posY, uint8_t state);

  virtual uint8_t getState() const;

 protected:
  uint8_t _state;
};
