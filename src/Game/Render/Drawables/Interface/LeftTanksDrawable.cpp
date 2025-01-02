#include "LeftTanksDrawable.h"

#include "../../../../Other/Log.h"

LeftTanksDrawable::LeftTanksDrawable() {
  if (!_texture.loadFromFile(Path::getAbsolutePath("resources/graphics/TankSmall.png"))) {
    throw std::runtime_error(R"(Cannot load "resources/graphics/TankSmall.png" texture)");
  }
  _layer = 210;
  Log::debug(R"(Drawable "LeftTanks" created)");
}

void LeftTanksDrawable::update(const std::shared_ptr<IObject> &object) {
  while (object->getState() > _sprites.size()) {
    _sprites.emplace_back(_texture);
  }
  while (object->getState() < _sprites.size()) {
    _sprites.erase(_sprites.begin() + _sprites.size() - 1);
  }
  for (auto i = 0; i < _sprites.size(); ++i) {
    _sprites[i].setPosition(object->getPosition() + sf::Vector2f((i % 2) * 8, (i / 2) * 8));
  }
}
