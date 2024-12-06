#include "IMovable.h"

IMovable::IMovable(ObjectType type, const sf::Vector2f &position, const sf::Vector2f &size, const ObjectRotation &rotation, const double speed) :
IObject(type, position, size), _rotation(rotation), _speed(speed) {}

IMovable::IMovable(ObjectType type, const sf::Vector2f &position, const sf::Vector2f &size, const double speed) : IMovable(type, position, size, ObjectRotation::Up, speed) {}

size_t IMovable::move(Game& game, const bool doMove) {
  if (!doMove || _lastMoveTime == -1 || _speed == 0) {
    _lastMoveTime = game.getTime();
    return 0;
  }

  // Moving
  size_t movedTiles = 0;
  while (game.getTime() >= _lastMoveTime + 1 / _speed) {
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

    _lastMoveTime += 1 / _speed;
    ++movedTiles;
  }
  return movedTiles;
}
