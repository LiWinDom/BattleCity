#include "TankDrawable.h"

#include "../../../Other/Log.h"

TankDrawable::TankDrawable() {
  if (!_texture.loadFromFile(Path::getAbsolutePath("resources/graphics/Tanks.png"))) {
    throw std::runtime_error(R"(Cannot load "resources/graphics/Tanks.png" texture)");
  }
  _sprites.emplace_back(_texture);
  Log::debug(R"(Drawable "PlayerTank" created)");
}

void TankDrawable::update(const std::shared_ptr<IObject> &object) {
  uint8_t state = object->getState();
  uint8_t rotation = state & 3;
  bool wheelState = state >> 2 & 1;
  _sprites[0].setTextureRect(sf::IntRect(rotation * 32 + wheelState * 16, 0, 16, 16));
  _sprites[0].setPosition(object->getPosition());
}
