#pragma once

#include "../IObject.h"

class PlayerLives : public IObject {
 public:
  PlayerLives(const uint8_t playerNum);

  uint8_t getState() const override;

  void setState(const uint8_t state);

 private:
  uint8_t _state = 0;
};
