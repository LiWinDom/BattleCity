#pragma once

#include "IObject.h"

class IMovable : public IObject {
 public:
  IMovable(ObjectType type, const sf::Vector2f& position, const sf::Vector2f& size, const ObjectRotation& rotation, const double speed);
  IMovable(ObjectType type, const sf::Vector2f& position, const sf::Vector2f& size, const double speed);

  size_t move(const sf::Clock& globalClock, const bool doMove = true);

 protected:
  ObjectRotation _rotation = ObjectRotation::Up;
  double _speed = 0;

 private:
  double _lastMoveTime = -1;
};
