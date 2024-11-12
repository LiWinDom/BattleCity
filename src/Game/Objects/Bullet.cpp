#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f& tankPosition, const ObjectRotation& rotation, const bool isFast) :
IObject(ObjectType::Bullet, {0, 0}, {4, 4}), _rotation(rotation) {
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

  _collistion = false;
  if (isFast) {
    _speed = 240;
  }
  else {
    _speed = 120;
  }
}

uint8_t Bullet::getState() const {
  return (uint8_t)_rotation;
}

void Bullet::think(std::vector<std::shared_ptr<IObject>> &objects, const sf::Clock &globalClock, const Event &event) {
  // Movement
  if (lastMoveTime == -1) {
    lastMoveTime = globalClock.getElapsedTime().asSeconds();
  }
  while (globalClock.getElapsedTime().asSeconds() >= lastMoveTime + 1 / _speed) {
    lastMoveTime += 1 / _speed;

    switch (_rotation) {
      case ObjectRotation::Up:
        --_position.y;
        break;
      case ObjectRotation::Left:
        --_position.x;
        break;
      case ObjectRotation::Down:
        ++_position.y;
        break;
      case ObjectRotation::Right:
        ++_position.x;
        break;
    }

    const auto collisions = getSoftCollisions(objects);
    if (collisions.empty()) {
      continue;
    }
    for (const auto object: collisions) {

    }
    _desytroyed = true;
  }
}
