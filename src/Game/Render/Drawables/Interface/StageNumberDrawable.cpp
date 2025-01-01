#include "StageNumberDrawable.h"

#include "../../../../Other/Log.h"

StageNumberDrawable::StageNumberDrawable() {
  if (!_texture.loadFromFile(Path::getAbsolutePath("resources/graphics/Numbers.png"))) {
    throw std::runtime_error(R"(Cannot load "resources/graphics/Numbers.png" texture)");
  }
  _sprites.emplace_back(_texture);
  _sprites.emplace_back(_texture);
  _layer = 210;
  Log::debug(R"(Drawable "StageNumber" created)");
}

void StageNumberDrawable::update(const std::shared_ptr<IObject> &object) {
  uint8_t lowerStage = (object->getState() + 1) % 10;
  uint8_t upperStage = (object->getState() + 1) / 10;

  _sprites[0].setTextureRect(sf::IntRect(upperStage * 8, 0, 8, 8));
  if (upperStage == 0) {
    _sprites[0].setTextureRect(sf::IntRect(0, 0, 0, 0));
  }
  _sprites[1].setTextureRect(sf::IntRect(lowerStage * 8, 0, 8, 8));
  _sprites[0].setPosition(object->getPosition());
  _sprites[1].setPosition(object->getPosition() + sf::Vector2f(8, 0));
}
