#pragma once

#include "Bullet.h"
#include "IMovable.h"

class ITank : public IMovable {
 public:
  ITank(ObjectType type, const sf::Vector2f& position);

  uint8_t getState() const override;

  void think(Game& game, const Event& event) override;

  void shoot(Game& game);

 protected:
  static void snap(float& coordinate);

  uint8_t _tankType = 0;
  bool _hasBonus = false;
  uint8_t _livesNum = 0;
  bool _wheelState = false;
  float _lastShotTime = -1;
  std::vector<std::shared_ptr<IObject>> _bullets;
};
