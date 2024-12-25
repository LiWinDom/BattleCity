#include "GameOverDrawable.h"

#include "../../../../Other/Log.h"

GameOverDrawable::GameOverDrawable() {
  if (!_texture.loadFromFile(Path::getAbsolutePath("resources/graphics/GameOver.png"))) {
    throw std::runtime_error(R"(Cannot load "resources/graphics/GameOver.png" texture)");
  }
  _sprites.emplace_back(_texture);
  _layer = 201;
  Log::debug(R"(Drawable "GameOver" created)");
}

void GameOverDrawable::update(const std::shared_ptr<IObject> &object) {
  _sprites[0].setPosition(object->getPosition());
}
