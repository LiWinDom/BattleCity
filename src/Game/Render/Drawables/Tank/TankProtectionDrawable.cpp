#include "TankProtectionDrawable.h"

#include "../../../../Other/Log.h"

TankProtectionDrawable::TankProtectionDrawable() {
  if (!_texture.loadFromFile(Path::getAbsolutePath("resources/graphics/Protection.png"))) {
    throw std::runtime_error(R"(Cannot load "resources/graphics/Protection.png" texture)");
  }
  _sprites.emplace_back(_texture);
  _layer = 5;
  Log::debug(R"(Drawable "TankProtection" created)");
}

void TankProtectionDrawable::update(const std::shared_ptr<IObject> &object) {
  _sprites[0].setTextureRect(sf::IntRect(object->getState() * 16, 0, 16, 16));
  _sprites[0].setPosition(object->getPosition());
}
