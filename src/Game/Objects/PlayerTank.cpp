#include "PlayerTank.h"

PlayerTank::PlayerTank(const sf::Vector2f& position) : ITank(ObjectType::PlayerTank, position) {}

void PlayerTank::think(const std::vector<std::shared_ptr<IObject>> &objects, const sf::Clock& globalClock, const Event& event) {
  static float holdTime = globalClock.getElapsedTime().asSeconds();
  if (event.up || event.down || event.left || event.right) {
    while (globalClock.getElapsedTime().asSeconds() >= holdTime + 1 / 45.0) {
      holdTime += 1 / 45.0;
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
      if (!findCollisions(objects).empty()) {
        _position = oldPosition;
      }
    }
  }
  else {
    holdTime = globalClock.getElapsedTime().asSeconds();
  }
}
