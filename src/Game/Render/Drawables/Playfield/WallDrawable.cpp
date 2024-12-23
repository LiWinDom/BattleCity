#include "WallDrawable.h"

#include "../../../../Other/Log.h"

WallDrawable::WallDrawable() {
  if (!_texture.loadFromFile(Path::getAbsolutePath("resources/graphics/Blocks.png"))) {
    throw std::runtime_error(R"(Cannot load "resources/graphics/Blocks.png" texture)");
  }
  _sprites.emplace_back(_texture);
  Log::debug(R"(Drawable "Wall" created)");
}

void WallDrawable::update(const std::shared_ptr<IObject> &object) {
  _sprites[0].setTextureRect(sf::IntRect(0, 4, 8, 8));
  _sprites[0].setPosition(object->getPosition());
}
