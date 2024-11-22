#include "IDrawable.h"

uint8_t IDrawable::getLayer() const {
  return _layer;
}

std::vector<sf::Sprite> IDrawable::getSprites() const {
  return _sprites;
}
