#include "Bullet.h"

#include "Explosion.h"
#include "ITank.h"

Bullet::Bullet(const sf::Vector2f& tankPosition, const ObjectRotation& rotation, const bool belongsToEnemy, const bool isFast, const bool isPowerful) :
IMovable(ObjectType::Bullet, {0, 0}, {4, 4}, rotation, isFast ? 240 : 120), _belongsToEnemy(belongsToEnemy), _isPowerful(isPowerful) {
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

  const auto collisions = getHardCollisions(game.getObjects());
  bool needToDestroy = false;
  bool destroyWithExplosion = false;

  for (const auto object: collisions) {
    switch (object->getType()) {
      case ObjectType::EnemyTank:
        if (_belongsToEnemy) {
          continue;
        }
        break;
      case ObjectType::PlayerTank:
        if (!_belongsToEnemy) {
          auto tank = dynamic_cast<ITank*>(object.get());
          tank->freeze(game, 3);
          needToDestroy = true;
          destroyWithExplosion = true;
          continue;
        }
        break;
      case ObjectType::Bullet:
        if (dynamic_cast<Bullet*>(object.get())->_belongsToEnemy == _belongsToEnemy) {
          continue;
        }
        break;
      case ObjectType::Water:
      case ObjectType::Bonus:
        continue;
    }
    object->destroy(game, _rotation);
    needToDestroy = true;
    if (object->getType() != ObjectType::Bullet) {
      destroyWithExplosion = true;
    }
  }
  if (needToDestroy) {
    _desytroyed = true;
    if (destroyWithExplosion) {
      game.addObject(std::make_shared<Explosion>(_position + sf::Vector2f(_size.x / 2, _size.y / 2), false));
    }
  }
}

void Bullet::destroy(Game &game, const ObjectRotation& bulletRotation) {
  _desytroyed = true;
}
