#pragma once

#include <cstdint>

#include "../IObject.h"

enum class BonusType : uint8_t {
  PlayerProtection = 0,
  TimeFreezer = 1,
  BaseProtection = 2,
  TankUpgrade = 3,
  Granade = 4,
  Life = 5,
};

class Bonus : public IObject {
 public:
  Bonus(Game& game);

  uint8_t getState() const override;

  void think(Game& game, const Event& event) override;

 private:
  BonusType _bonusType;
  bool _show = true;
};
