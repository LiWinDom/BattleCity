#include "EagleDrawable.h"

#include "../../../../Other/Log.h"

EagleDrawable::EagleDrawable() {
  if (!_texture.loadFromFile(Path::getAbsolutePath("resources/graphics/Eagle.png"))) {
    throw std::runtime_error(R"(Cannot load "resources/graphics/Eagle.png" texture)");
  }
  _sprites.emplace_back(_texture);
  Log::debug(R"(Drawable "Eagle" created)");
}

void EagleDrawable::update(const std::shared_ptr<IObject> &object) {
  _sprites[0].setTextureRect(sf::IntRect(object->getState() * 16, 0, 16, 16));
  _sprites[0].setPosition(object->getPosition());
}
