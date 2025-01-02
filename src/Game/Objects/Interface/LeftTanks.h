#pragma once

#include "../IObject.h"

class LeftTanks : public IObject {
 public:
  LeftTanks(const uint8_t tanksNum);

  uint8_t getState() const override;

  void removeTank();

 private:
  uint8_t _state;
};
