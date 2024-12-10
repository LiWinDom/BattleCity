#pragma once

#include "IMovable.h"

class Bullet : public IMovable {
 public:
  Bullet(const sf::Vector2f& tankPosition, const ObjectRotation& rotation, const bool isFast = false);

  uint8_t getState() const override;

  void think(Game& game, const Event& event) override;

  void destroy(Game& game, const ObjectRotation bulletRotation) override;
};
