#pragma once

#include "SFML/Graphics.hpp"
#include <vector>

#include "../../Objects/IObject.h"

class IDrawable {
 public:
  std::vector<sf::Sprite> getSprites() const;

  virtual void update(const std::shared_ptr<IObject>& object) = 0;

 protected:
  sf::Texture _texture;
  std::vector<sf::Sprite> _sprites;
};
