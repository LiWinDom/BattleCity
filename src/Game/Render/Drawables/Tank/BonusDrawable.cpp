#include "BonusDrawable.h"

#include "../../../../Other/Log.h"

BonusDrawable::BonusDrawable() {
  if (!_texture.loadFromFile(Path::getAbsolutePath("resources/graphics/Bonuses.png"))) {
    throw std::runtime_error(R"(Cannot load "resources/graphics/Bonuses.png" texture)");
  }
  _sprites.emplace_back(_texture);
  _layer = 7;
  Log::debug(R"(Drawable "Bonus" created)");
}

void BonusDrawable::update(const std::shared_ptr<IObject> &object) {
  auto state = object->getState();
  if ((state & 8) == 0) {
    _sprites[0].setTextureRect(sf::IntRect(0, 0, 0, 0));
    return;
  }
  _sprites[0].setTextureRect(sf::IntRect((state & 7) * 16, 0, 16, 16));
  _sprites[0].setPosition(object->getPosition());
}
