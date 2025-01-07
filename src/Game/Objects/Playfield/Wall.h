#pragma once

#include "IBlock.h"

class Wall : virtual public IBlock {
 public:
  Wall(const sf::Vector2f& position);
};
