#pragma once

#include "../IObject.h"

class TankProtection : public IObject {
 public:
  TankProtection(IObject* tank, float protectionUntil);

  uint8_t getState() const override;

  void think(Game& game, const Event& event) override;

 private:
  IObject* _tankPointer = nullptr;
  float _protectionUntil = -1;

  bool _state = false;
};
