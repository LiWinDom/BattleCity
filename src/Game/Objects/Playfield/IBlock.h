#pragma once

#include "../IObject.h"

class IBlock : public IObject {
 public:
  IBlock(ObjectType type, const sf::Vector2f& position);
};
