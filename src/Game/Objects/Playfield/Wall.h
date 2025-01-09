#pragma once

#include "IBlock.h"

class Wall : virtual public IBlock {
 public:
  Wall(const sf::Vector2f& position);

  void destroy(Game &game, const ObjectRotation &bulletRotation, const bool powerfulBullet = false) override;
};
