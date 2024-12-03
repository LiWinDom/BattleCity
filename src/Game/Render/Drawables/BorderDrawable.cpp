#include "BorderDrawable.h"

#include "../../../Other/Log.h"

BorderDrawable::BorderDrawable() {
  if (!_texture.loadFromFile(Path::getAbsolutePath("resources/graphics/StatsBackground.png"))) {
    throw std::runtime_error(R"(Cannot load "resources/graphics/StatsBackground.png" texture)");
  }
  _sprites.emplace_back(_texture);
  _sprites[0].setTextureRect(sf::IntRect(0, 0, 32, 208));
  _layer = 2;
  Log::debug(R"(Drawable "Border" created)");
}

void BorderDrawable::update(const std::shared_ptr<IObject> &object) {
  _sprites[0].setPosition(object->getPosition());
}
