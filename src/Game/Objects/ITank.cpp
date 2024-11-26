#include "ITank.h"

ITank::ITank(ObjectType type, const sf::Vector2f& position) : IMovable(type, position, sf::Vector2f(16, 16), 45) {
  _collisionLayer = 1;
}

uint8_t ITank::getState() const {
  return _tankType << 6
    | _hasBonus << 5
    | _livesNum << 3
    | _wheelState << 2
    | (uint8_t)_rotation; // [type][type][hasBonus/playerNum][livesNum][livesNum][wheelState][rotation][rotation]
}

void ITank::think(std::vector<std::shared_ptr<IObject>> &objects, const sf::Clock &globalClock, const Event &event) {
  // Getting pressed keys
  PressedButtons pressed;
  if (_type == ObjectType::PlayerTank) {
    if (_hasBonus == 0) {
      pressed = event.player1;
    }
    else {
      pressed = event.player2;
    }
  }
  else {
    pressed;
  }

  // Movement
  if (pressed.up || pressed.down || pressed.left || pressed.right) {
    auto oldPosition = _position;

    // Rotating and snapping
    if (pressed.up) {
      snap(_position.x);
      snap(oldPosition.x);
      _rotation = ObjectRotation::Up;
    } else if (pressed.left) {
      snap(_position.y);
      snap(oldPosition.y);
      _rotation = ObjectRotation::Left;
    } else if (pressed.down) {
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
  if (pressed.shoot) {
    shoot(objects);
  }

  // Deleting destroyed bullets
  for (auto i = 0; i < _bullets.size(); ++i) {
    if (_bullets[i]->isDestroyed()) {
      _bullets.erase(_bullets.begin() + i);
      --i;
    }
  }
}

void ITank::shoot(std::vector<std::shared_ptr<IObject>> &objects) {
  uint8_t maxBullets = 1;
  if (_type == ObjectType::PlayerTank) {
    if (_tankType >= 2) {
      maxBullets = 2;
    }
  }
  if (_bullets.size() >= maxBullets) {
    // Too many bullets
    return;
  }

  const auto bullet = std::make_shared<Bullet>(_position, _rotation);
  objects.push_back(bullet);
  _bullets.push_back(bullet);
}

void ITank::snap(float& coordinate) {
  if ((int)coordinate % 8 > 4) {
    coordinate += 8;
  }
  coordinate -= (int)coordinate % 8;
}
