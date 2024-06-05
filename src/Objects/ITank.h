#ifndef BATTLECITY_SERVER_ITANK_H
#define BATTLECITY_SERVER_ITANK_H

#include "../IObject.h"

class ITank : public IObject {
 public:
  ITank(const sf::Vector2i& position);
 private:
};


#endif //BATTLECITY_SERVER_ITANK_H
