#include "PlayerTank.h"

PlayerTank::PlayerTank(const sf::Vector2f& position) : ITank(ObjectType::PlayerTank, position) {}

void PlayerTank::think(const std::vector<std::shared_ptr<IObject>> &objects, uint16_t index, const sf::Clock& globalClock, const Event& event) {
  static float holdTime = globalClock.getElapsedTime().asSeconds();
  if (event.up || event.down || event.left || event.right) {
    while (globalClock.getElapsedTime().asSeconds() >= holdTime + 1 / 45.0) {
      holdTime += 1 / 45.0;
      if (event.up) {
        _rotation = 0;
        --_position.y;
      }
      else if (event.left) {
        _rotation = 1;
        --_position.x;
      }
      else if (event.down) {
        _rotation = 2;
        ++_position.y;
      }
      else {
        _rotation = 3;
        ++_position.x;
      }
    }
  }
  else {
    holdTime = globalClock.getElapsedTime().asSeconds();
  }
}
