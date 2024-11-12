#pragma once

#include "IObject.h"

class ITank : public IObject {
 public:
  ITank(ObjectType type, const sf::Vector2f& position);

  uint8_t getState() const override;

 protected:
   void snap(float& coordinate);

   ObjectRotation _rotation = ObjectRotation::Up;
   bool _wheelState = false;

  double lastMoveTime = -1;
};
