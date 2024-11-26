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
  // [type][type][hasBonus/playerNum][livesNum][livesNum][wheelState][rotation][rotation]
  uint8_t tankType = state >> 6;
  bool hasBonus = state >> 5 & 1;
  uint8_t livesNum = state >> 3 & 3;
  bool wheelState = state >> 2 & 1;
  uint8_t rotation = state & 3;

  if (object->getType() == ObjectType::PlayerTank) {
    _sprites[0].setTextureRect(sf::IntRect(hasBonus * 128 + rotation * 32 + wheelState * 16, tankType * 16, 16, 16));
  }
  else {
    _sprites[0].setTextureRect(sf::IntRect(3 * 128 + rotation * 32 + wheelState * 16, 64 + tankType * 16, 16, 16));
  }
  _sprites[0].setPosition(object->getPosition());
}
