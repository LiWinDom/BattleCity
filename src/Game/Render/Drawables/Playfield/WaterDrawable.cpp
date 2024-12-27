#include "WaterDrawable.h"

#include "../../../../Other/Log.h"

WaterDrawable::WaterDrawable() {
  if (!_texture.loadFromFile(Path::getAbsolutePath("resources/graphics/Blocks.png"))) {
    throw std::runtime_error(R"(Cannot load "resources/graphics/Blocks.png" texture)");
  }
  _sprites.emplace_back(_texture);
  Log::debug(R"(Drawable "Water" created)");
}

void WaterDrawable::update(const std::shared_ptr<IObject> &object) {
  _sprites[0].setTextureRect(sf::IntRect(object->getState() * 8, 12, 8, 8));
  _sprites[0].setPosition(object->getPosition());
}
