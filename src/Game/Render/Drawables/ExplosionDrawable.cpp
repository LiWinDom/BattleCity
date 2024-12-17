#include "ExplosionDrawable.h"

#include "../../../Other/Log.h"

ExplosionDrawable::ExplosionDrawable() {
  if (!_texture.loadFromFile(Path::getAbsolutePath("resources/graphics/Explosion.png"))) {
    throw std::runtime_error(R"(Cannot load "resources/graphics/Explosion.png" texture)");
  }
  _layer = 3;
  _sprites.emplace_back(_texture);
  Log::debug(R"(Drawable "Explosion" created)");
}

void ExplosionDrawable::update(const std::shared_ptr<IObject> &object) {
  auto frame = object->getState();
  _sprites[0].setTextureRect(sf::IntRect(frame * 32, 0, 32, 32));
  _sprites[0].setPosition(object->getPosition() - sf::Vector2f(16, 16));
}
