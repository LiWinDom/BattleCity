#include "PlayerLivesDrawable.h"

#include "../../../../Other/Log.h"

PlayerLivesDrawable::PlayerLivesDrawable() {
  if (!_texture.loadFromFile(Path::getAbsolutePath("resources/graphics/Numbers.png"))) {
    throw std::runtime_error(R"(Cannot load "resources/graphics/Numbers.png" texture)");
  }
  _sprites.emplace_back(_texture);
  _layer = 210;
  Log::debug(R"(Drawable "PlayerLives" created)");
}

void PlayerLivesDrawable::update(const std::shared_ptr<IObject> &object) {
  _sprites[0].setTextureRect(sf::IntRect(object->getState() * 8, 0, 8, 8));
  _sprites[0].setPosition(object->getPosition());
}
