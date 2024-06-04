#include "IObject.h"

#include "Log.h"

IObject::IObject(const sf::Vector2f& position, const sf::Vector2u& size, ObjectType type) : _type(type) {
  _sprite.setPosition(position);

  if (!_texture.loadFromFile(Path::getAbsolutePath("resources/graphics/Eagle.png"))) {
    Log::error("Cannot load texture");
  }

  _sprite.setTexture(_texture);
  _sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
}
