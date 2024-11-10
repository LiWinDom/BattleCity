#pragma once

#include "IObject.h"

class ITank : public IObject {
 public:
  ITank(ObjectType type, const sf::Vector2f& position);

  uint8_t getState() const override;

 protected:
   void snap(float& coordinate);

   uint8_t _rotation = 0;
   bool _wheelState = false;
};
