#include "TankSpawnerDrawable.h"

#include "../../../../Other/Log.h"

TankSpawnerDrawable::TankSpawnerDrawable() {
  if (!_texture.loadFromFile(Path::getAbsolutePath("resources/graphics/Spawn.png"))) {
    throw std::runtime_error(R"(Cannot load "resources/graphics/Spawn.png" texture)");
  }
  _sprites.emplace_back(_texture);
  _layer = 1;
  Log::debug(R"(Drawable "TankSpawner" created)");
}

void TankSpawnerDrawable::update(const std::shared_ptr<IObject> &object) {
  uint8_t state = object->getState();
  switch (state) {
    case 4:
      state = 2;
      break;
    case 5:
      state = 1;
      break;
  }
  _sprites[0].setTextureRect(sf::IntRect((state) * 16, 0, 16, 16));
  _sprites[0].setPosition(object->getPosition());
}
