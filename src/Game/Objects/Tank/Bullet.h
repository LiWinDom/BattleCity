#pragma once

#include "../IMovable.h"

class Bullet : public IMovable {
 public:
  Bullet(const sf::Vector2f& tankPosition, const ObjectRotation& rotation, const bool belongsToEnemy, const bool isFast, const bool isPowerful);

  uint8_t getState() const override;

  void think(Game& game, const Event& event) override;

  void destroy(Game& game, const ObjectRotation& bulletRotation = ObjectRotation::Up, const bool powerfulBullet = false) override;

 private:
  bool _belongsToEnemy, _isPowerful;
};
