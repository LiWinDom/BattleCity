#include "BulletDrawable.h"

#include "../../../../Other/Log.h"

BulletDrawable::BulletDrawable() {
  if (!_texture.loadFromFile(Path::getAbsolutePath("resources/graphics/Bullets.png"))) {
    throw std::runtime_error(R"(Cannot load "resources/graphics/Bullets.png" texture)");
  }
  _sprites.emplace_back(_texture);
  Log::debug(R"(Drawable "Bullet" created)");
}

void BulletDrawable::update(const std::shared_ptr<IObject> &object) {
  _sprites[0].setTextureRect(sf::IntRect(object->getState() * 4, 0, 4, 4));
  _sprites[0].setPosition(object->getPosition());
}
