#include "IObject.h"

IObject::IObject(const sf::Vector2f &position, const sf::Vector2u &size, const ObjectType type) : _type(type) {
  _sprite.setOrigin(0, 0);
  _sprite.setPosition(position);

  if (!_texture.loadFromFile());
}
