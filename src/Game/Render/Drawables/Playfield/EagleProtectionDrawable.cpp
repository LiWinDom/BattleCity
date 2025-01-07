#include "EagleProtectionDrawable.h"

#include "../../../../Other/Log.h"

EagleProtectionDrawable::EagleProtectionDrawable() {
  if (!_texture.loadFromFile(Path::getAbsolutePath("resources/graphics/Blocks.png"))) {
    throw std::runtime_error(R"(Cannot load "resources/graphics/Blocks.png" texture)");
  }
  for (auto i = 0; i < 4; ++i) {
    _sprites.emplace_back(_texture);
  }
  Log::debug(R"(Drawable "EagleProtection" created)");
}

void EagleProtectionDrawable::update(const std::shared_ptr<IObject> &object) {
  const auto state = object->getState() & 15;
  const auto blockType = object->getState() >> 4;

  for (auto i = 0; i < 4; ++i) {
    if (blockType == 0) {
      _sprites[i].setTextureRect(sf::IntRect(0, 0, 0, 0));
    }
    else if (blockType == 1) {
      if (((state >> i) & 1) == false) {
        _sprites[i].setTextureRect(sf::IntRect(0, 0, 0, 0));
      }
      else {
        _sprites[i].setTextureRect(sf::IntRect(i * 4, 0, 4, 4));
      }
    }
    else if (blockType == 2) {
      if (i == 0) {
        _sprites[0].setTextureRect(sf::IntRect(0, 4, 8, 8));
      }
      else {
        _sprites[i].setTextureRect(sf::IntRect(0, 0, 0, 0));
      }
    }
    _sprites[i].setPosition(object->getPosition() + sf::Vector2f((i % 2) * 4, (i / 2) * 4));
  }
}
