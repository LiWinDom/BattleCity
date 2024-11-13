#pragma once

#include "IMovable.h"

class ITank : public IMovable {
 public:
  ITank(ObjectType type, const sf::Vector2f& position);

  uint8_t getState() const override;

 protected:
  static void snap(float& coordinate);

  bool _wheelState = false;
};
