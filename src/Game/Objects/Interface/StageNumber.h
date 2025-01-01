#pragma once

#include "../IObject.h"

class StageNumber : public IObject {
 public:
  StageNumber();

  uint8_t getState() const override;

  void think(Game& game, const Event& event) override;

 private:
  uint8_t _state = 0;
};
