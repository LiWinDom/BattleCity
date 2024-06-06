#ifndef BATTLECITY_ITANK_H
#define BATTLECITY_ITANK_H

#include "../IObject.h"

class ITank : public IObject {
 public:
  ITank(ObjectType type, const sf::Vector2f& position);

  uint8_t getState() const override;

 protected:
    uint8_t _rotation = 0;
};


#endif //BATTLECITY_ITANK_H
