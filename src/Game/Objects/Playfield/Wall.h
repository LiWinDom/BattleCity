#pragma once

#include "IBlock.h"

class Wall : public IBlock {
 public:
  Wall(const sf::Vector2f& position);
};
