#include "Wall.h"

Wall::Wall(const sf::Vector2f& position) : IBlock(ObjectType::Wall, position) {}

void Wall::destroy(Game &game, const ObjectRotation &bulletRotation, const bool powerfulBullet) {
  if (powerfulBullet) {
    _desytroyed = true;
  }
}
