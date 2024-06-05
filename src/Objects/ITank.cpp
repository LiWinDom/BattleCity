#include "ITank.h"

#include "../Log.h"

ITank::ITank(const sf::Vector2i &position) : IObject() {
  if (!_texture.loadFromFile(Path::getAbsolutePath("resources/graphics/Tanks.png"))) {
    throw std::runtime_error(R"(Cannot load "resources/graphics/Tanks.png")");
  }
  _sprites.push_back(sf::Sprite(_texture, sf::IntRect(0, 0, position.x, position.y)));
}
