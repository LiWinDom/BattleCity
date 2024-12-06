#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f& tankPosition, const ObjectRotation& rotation, const bool isFast) :
IMovable(ObjectType::Bullet, {0, 0}, {4, 4}, rotation, isFast ? 240 : 120) {
  _collisionLayer = 2;
  switch (rotation) {
    case ObjectRotation::Up:
      _position = tankPosition + sf::Vector2f(6, -4);
      break;
    case ObjectRotation::Left:
      _position = tankPosition + sf::Vector2f(-4, 6);
      break;
    case ObjectRotation::Down:
      _position = tankPosition + sf::Vector2f(6, 16);
      break;
    case ObjectRotation::Right:
      _position = tankPosition + sf::Vector2f(16, 6);
  }
}

uint8_t Bullet::getState() const {
  return (uint8_t)_rotation;
}

void Bullet::think(Game& game, const Event &event) {
  // Movement
  move(game);

  const auto collisions = getSoftCollisions(game.getObjects());
  if (collisions.empty()) {
    return;
  }
  for (const auto object: collisions) {
    object->destroy(game, _rotation);
  }
  _desytroyed = true;
}
