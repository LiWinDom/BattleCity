#include "BrickDrawable.h"

#include "../../../Other/Log.h"

BrickDrawable::BrickDrawable() {
  if (!_texture.loadFromFile(Path::getAbsolutePath("resources/graphics/Blocks.png"))) {
    throw std::runtime_error(R"(Cannot load "resources/graphics/Blocks.png" texture)");
  }
  for (auto i = 0; i < 4; ++i) {
    _sprites.emplace_back(_texture);
    _sprites[i].setTextureRect(sf::IntRect(i * 4, 0, 4, 4));
  }
  Log::debug(R"(Drawable "Brick" created)");
}

void BrickDrawable::update(const std::shared_ptr<IObject> &object) {
  const auto state = object->getState();
  for (auto i = 0; i < 4; ++i) {
    if (((state >> i) & 1) == false) {
      _sprites[i].setTextureRect(sf::IntRect(20, 0, 4, 4));
    }
    _sprites[i].setPosition(object->getPosition() + sf::Vector2f((i % 2) * 4, (i / 2) * 4));
  }
}
