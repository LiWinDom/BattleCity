#include "PlayerTank.h"

PlayerTank::PlayerTank(TankSpawner* spawner) : ITank(ObjectType::PlayerTank, spawner->getPosition()), _spawnerPointer(spawner) {
  _hasBonus = spawner->getSpawnerNum();
}

uint8_t PlayerTank::getState() const {
  return ITank::getState() | _hasBonus << 3;
}

void PlayerTank::think(Game& game, const Event& event) {
  if (_protectedUntil == -1) {
    addProtection(game, 2);
  }
  // Base think
  ITank::think(game, event);
}

void PlayerTank::upgrade() {
  _tankType = std::min(_tankType + 1, 3);

  if (_tankType == 1) {
    _fastBullets = true;
  }
  else if (_tankType == 2) {
    _maxBullets = 2;
  }
  else {
    _powerfulBullets = true;
  }
}

void PlayerTank::addLife() {
  _spawnerPointer->addLife();
}
