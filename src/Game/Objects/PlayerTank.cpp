#include "PlayerTank.h"

#include "Bullet.h"

PlayerTank::PlayerTank(const sf::Vector2f& position) : ITank(ObjectType::PlayerTank, position) {}

void PlayerTank::think(std::vector<std::shared_ptr<IObject>> &objects, const sf::Clock& globalClock, const Event& event) {
  // Movement
  if (event.up || event.down || event.left || event.right) {
    auto oldPosition = _position;

    // Rotating and snapping
    if (event.up) {
      snap(_position.x);
      snap(oldPosition.x);
      _rotation = ObjectRotation::Up;
    } else if (event.left) {
      snap(_position.y);
      snap(oldPosition.y);
      _rotation = ObjectRotation::Left;
    } else if (event.down) {
      snap(_position.x);
      snap(oldPosition.x);
      _rotation = ObjectRotation::Down;
    } else {
      snap(_position.y);
      snap(oldPosition.y);
      _rotation = ObjectRotation::Right;
    }

    const auto movedTiles = move(globalClock);
    if (movedTiles % 2) {
      _wheelState = !_wheelState;
    }
    if (!getHardCollisions(objects).empty()) {
      _position = oldPosition;
    }
  }
  else {
    move(globalClock, false);
  }

  // Shooting
  if (event.shoot) {
    objects.push_back(std::make_shared<Bullet>(_position, _rotation));
  }
}
