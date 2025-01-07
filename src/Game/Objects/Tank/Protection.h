#pragma once

#include "../IObject.h"

class Protection : public IObject {
 public:
  Protection(IObject* tank, float protectionUntil);

  uint8_t getState() const override;

  void think(Game& game, const Event& event) override;

 private:
  IObject* _tankPointer = nullptr;
  float _protectionUntil = -1;

  bool _state = false;
};
