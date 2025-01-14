#include "EnemyTank.h"

#include "Bullet.h"

EnemyTank::EnemyTank(const sf::Vector2f& position, const uint8_t tankType, const bool hasBonus) : ITank(ObjectType::EnemyTank, position) {
  _tankType = tankType;
  _hasBonus = hasBonus;
  _speed = 30;

  switch (_tankType) {
    case 0:
      // Simple tank
      break;
    case 1:
      // Fast tank
      _speed = 60;
      break;
    case 2:
      // Fast bullet tank
      _fastBullets = true;
      break;
    case 3:
      // Heavy tank
      _livesNum = 3;
      break;
  }

  _event.player1.down = true;
}

uint8_t EnemyTank::getState() const {
  return ITank::getState() | _color << 3;
}

void EnemyTank::changeColor(const Game& game) {
  if (_bonusBlinkTime == -1) {
    _bonusBlinkTime = game.getTime();
  }
  if (_livesChangeTime == -1) {
    _livesChangeTime = game.getTime();
  }

  if (_hasBonus) {
    while (_bonusBlinkTime + 1.0 / 6 < game.getTime()) {
      if (_color == 0b11) {
        _color = 0b10;
      } else {
        _color = 0b11;
      }
      _bonusBlinkTime += 1.0 / 6;
    }
  }

  if (_color != 0b11) {
    while (_livesChangeTime + 1.0 / 60 < game.getTime()) {
      if (_livesNum == 0) {
        _color = 0b10;
      }
      else if (_livesNum == 1) {
        // Yellow - Green
        if (_color == 0b00) {
          _color = 0b01;
        }
        else {
          _color = 0b00;
        }
      }
      else if (_livesNum == 2) {
        // White - Yellow
        if (_color == 0b10) {
          _color = 0b00;
        }
        else {
          _color = 0b10;
        }
      }
      else {
        // White - Green
        if (_color == 0b10) {
          _color = 0b01;
        }
        else {
          _color = 0b10;
        }
      }
      _livesChangeTime += 1.0 / 60;
    }
  }
}

void EnemyTank::think(Game& game, const Event& event) {
  // Modifying _event
  if ((int)_position.x % 8 == 0 && (int)_position.y % 8 == 0 && std::rand() % 16 == 0) {
    changeDirection(game);
  }
  else if (_failedToMove) {
    if (std::rand() % 4 == 0) {
      if ((int)_position.x % 8 || (int)_position.y % 8) {
        rotateClockwise();
        rotateClockwise();
      }
      else {
        changeDirection(game);
      }
    }
  }
  if (_bullets.empty()) {
    if (std::rand() % 32 == 0) {
      _event.player1.shoot = true;
    }
  }

  // Base think
  ITank::think(game, _event);
  _event.player1.shoot = false;

  changeColor(game);
}

void EnemyTank::upgrade() {
  _tankType = std::min(_tankType + 1, 3);

  if (_tankType == 1) {
    _speed = 60;
  }
  else if (_tankType == 2) {
    _speed = 30;
    _fastBullets = true;
  }
  else {
    _fastBullets = false;
    _livesNum = 3;
  }
}

void EnemyTank::addLife() {
  _livesNum = std::min(_livesNum + 1, 3);
}

void EnemyTank::changeDirection(Game &game) {
  // TODO: second and third period
  if (std::rand() % 2) {
    rotateClockwise();
  }
  else {
    rotateCounterClockwise();
  }
}

void EnemyTank::rotateClockwise() {
  if (_event.player1.up) {
    _event.player1.up = false;
    _event.player1.right = true;
  }
  else if (_event.player1.right) {
    _event.player1.right = false;
    _event.player1.down = true;
  }
  else if (_event.player1.down) {
    _event.player1.down = false;
    _event.player1.left = true;
  }
  else if (_event.player1.left) {
    _event.player1.left = false;
    _event.player1.up = true;
  }
}

void EnemyTank::rotateCounterClockwise() {
  // Reusing code
  rotateClockwise();
  rotateClockwise();
  rotateClockwise();
}
