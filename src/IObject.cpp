#include "IObject.h"

#include "Log.h"

IObject::IObject(const sf::Vector2f& position, const sf::Vector2u& size, ObjectType type) : _type(type) {
  _sprites.push_back(sf::Sprite());
  _sprites[0].setPosition(position);

  if (!_texture.loadFromFile(Path::getAbsolutePath("resources/graphics/Eagle.png"))) {
    Log::error("Cannot load texture");
  }

  _sprites[0].setTexture(_texture);
  _sprites[0].setTextureRect(sf::IntRect(0, 0, 16, 16));
}
