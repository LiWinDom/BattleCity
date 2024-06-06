#include "Drawable.h"

#include "../Log.h"

Drawable::Drawable(const IObject& object) {
  if (!_texture.loadFromFile(Path::getAbsolutePath("resources/Graphics.png"))) {
    throw std::runtime_error(R"(Cannot load "resources/Graphics.png" texture)");
  }

  switch (object.getType()) {
    case ObjectType::PlayerTank:
      _sprites.emplace_back(_texture);
      Log::info(R"(Drawable "PlayerTank" created)");
      break;

    default:
      Log::error("Drawable: Undefined object type");
  }
  update(object);
}

std::vector<sf::Sprite> Drawable::getSprites() const {
  return _sprites;
}

void Drawable::update(const IObject &object) {
  switch (object.getType()) {
    case ObjectType::PlayerTank:
      updateTank(object);
      break;
  }
}

void Drawable::updateTank(const IObject& object) {
  _sprites[0].setTextureRect(sf::IntRect(0, 0, 16, 16));
  _sprites[0].setPosition(object.getPosition());
}
