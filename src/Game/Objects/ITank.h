#ifndef BATTLECITY_ITANK_H
#define BATTLECITY_ITANK_H

#include "../IObject.h"

class ITank : public IObject {
 public:
  ITank(ObjectType type, const sf::Vector2f& position);

  uint16_t getState() const override;

 protected:

};


#endif //BATTLECITY_ITANK_H
