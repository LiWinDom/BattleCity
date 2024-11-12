#include "PlayerTank.h"

#include "Bullet.h"

PlayerTank::PlayerTank(const sf::Vector2f& position) : ITank(ObjectType::PlayerTank, position) {}

void PlayerTank::think(std::vector<std::shared_ptr<IObject>> &objects, const sf::Clock& globalClock, const Event& event) {
  // Movement
  static double lastMoveTime = globalClock.getElapsedTime().asSeconds();
  if (event.up || event.down || event.left || event.right) {
    while (globalClock.getElapsedTime().asSeconds() >= lastMoveTime + 1 / _speed) {
      lastMoveTime += 1 / _speed;
      _wheelState = !_wheelState;

      auto oldPosition = _position;
      if (event.up) {
        snap(_position.x);
        snap(oldPosition.x);
        _rotation = ObjectRotation::Up;
        --_position.y;
      }
      else if (event.left) {
        snap(_position.y);
        snap(oldPosition.y);
        _rotation = ObjectRotation::Left;
        --_position.x;
      }
      else if (event.down) {
        snap(_position.x);
        snap(oldPosition.x);
        _rotation = ObjectRotation::Down;
        ++_position.y;
      }
      else {
        snap(_position.y);
        snap(oldPosition.y);
        _rotation = ObjectRotation::Right;
        ++_position.x;
      }
      if (!getHardCollisions(objects).empty()) {
        _position = oldPosition;
      }
    }
  }
  else {
    lastMoveTime = globalClock.getElapsedTime().asSeconds();
  }

  // Shooting
  if (event.shoot) {
    objects.push_back(std::make_shared<Bullet>(_position + sf::Vector2f(6, -4), _rotation));
  }
}
