#include "PlayerTank.h"

PlayerTank::PlayerTank(const sf::Vector2f& position) : ITank(ObjectType::PlayerTank, position) {}

void PlayerTank::think(const std::vector<std::shared_ptr<IObject>> &objects, uint16_t index, const sf::Clock& globalClock, const Event& event) {
  static float holdTime = globalClock.getElapsedTime().asSeconds();
  if (event.up || event.down || event.left || event.right) {
    while (globalClock.getElapsedTime().asSeconds() >= holdTime + 1 / 45.0) {
      holdTime += 1 / 45.0;
      _wheelState = !_wheelState;

      const auto oldPosition = _position;
      if (event.up) {
        snap(_position.x);
        _rotation = 0;
        --_position.y;
      }
      else if (event.left) {
        snap(_position.y);
        _rotation = 1;
        --_position.x;
      }
      else if (event.down) {
        snap(_position.x);
        _rotation = 2;
        ++_position.y;
      }
      else {
        snap(_position.y);
        _rotation = 3;
        ++_position.x;
      }
      if (!findIntersection(objects).empty()) {
        _position = oldPosition;
      }
    }
  }
  else {
    holdTime = globalClock.getElapsedTime().asSeconds();
  }
}
