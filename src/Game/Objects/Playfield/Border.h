#pragma once

#include "../IObject.h"

class Border : public IObject {
 public:
  Border(uint8_t borderNum);

  uint8_t getState() const override;

 private:
  uint8_t _borderNum;
};
