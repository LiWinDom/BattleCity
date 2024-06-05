#include "IObject.h"

std::vector<sf::Sprite> IObject::getSprites() const {
  return _sprites;
}

sf::Vector2f IObject::getPosition() const {
  return _sprites.empty() ? sf::Vector2f(0, 0) : _sprites[0].getPosition();
}

void IObject::setPosition(const sf::Vector2f &position) {
  for (auto& sprite : _sprites) {
    sprite.setPosition(position);
  }
}
