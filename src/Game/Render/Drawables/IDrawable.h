#pragma once

#include "SFML/Graphics.hpp"
#include <vector>

#include "../../Objects/IObject.h"

class IDrawable {
 public:
  std::vector<sf::Sprite> getSprites() const;

  uint8_t getLayer() const;

  virtual void update(const std::shared_ptr<IObject>& object) = 0;

 protected:
  uint8_t _layer = 0;
  sf::Texture _texture;
  std::vector<sf::Sprite> _sprites;
};
