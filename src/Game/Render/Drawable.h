#ifndef BATTLECITY_DRAWABLE_H
#define BATTLECITY_DRAWABLE_H

#include "SFML/Graphics.hpp"
#include <vector>

#include "../IObject.h"

class Drawable final {
 public:
  Drawable(const IObject& object);

  std::vector<sf::Sprite> getSprites() const;

  void update(const IObject& object);

 private:
  void updateTank(const IObject& object);

  sf::Texture _texture;
  std::vector<sf::Sprite> _sprites;
};


#endif //BATTLECITY_DRAWABLE_H
