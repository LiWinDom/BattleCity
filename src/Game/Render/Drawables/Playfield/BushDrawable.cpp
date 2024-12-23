#include "BushDrawable.h"

#include "../../../../Other/Log.h"

BushDrawable::BushDrawable() {
  if (!_texture.loadFromFile(Path::getAbsolutePath("resources/graphics/Blocks.png"))) {
    throw std::runtime_error(R"(Cannot load "resources/graphics/Blocks.png" texture)");
  }
  _sprites.emplace_back(_texture);
  _layer = 2;
  Log::debug(R"(Drawable "Bush" created)");
}

void BushDrawable::update(const std::shared_ptr<IObject> &object) {
  _sprites[0].setTextureRect(sf::IntRect(8, 4, 8, 8));
  _sprites[0].setPosition(object->getPosition());
}
