#pragma once

#include "IBlock.h"

class Brick : virtual public IBlock {
 public:
  Brick(const sf::Vector2f& position);

  uint8_t getState() const override;

  void destroy(Game& game, const ObjectRotation& bulletRotation, const bool powerfulBullet = false) override;

 protected:
  uint8_t _state = 15;
};
