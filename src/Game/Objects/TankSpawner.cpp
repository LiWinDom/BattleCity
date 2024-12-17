#include "TankSpawner.h"

#include <exception>

#include "PlayerTank.h"

TankSpawner::TankSpawner(const sf::Vector2f& position, const ObjectType spawnObject, const uint8_t spawnerNum) :
IObject(ObjectType::Spawner, position, {16, 16}), _spawnObject(spawnObject), _spawnerNum(spawnerNum) {
  if (_spawnObject != ObjectType::PlayerTank && _spawnObject != ObjectType::EnemyTank) {
    throw std::invalid_argument("spawnObject expected to be PlayerTank or EnemyTank");
  }
  _collision = false;
}

uint8_t TankSpawner::getState() const {
  return _currentFrame;
}

void TankSpawner::think(Game& game, const Event &event) {
  if (_animationStartTime == -1) {
    // Game start
    _animationStartTime = game.getTime();
  }

  // Delay, animation
  if (_animationStartTime > game.getTime()) {
    // Waiting
    return;
  }
  else if (_animationStartTime + 64.0 / 60 > game.getTime()) {
    // TODO: animation calculation
    return;
  }
  else {
    // Spawning
    if (_spawnObject == ObjectType::PlayerTank) {
      if (_spawnedTank == nullptr && _spawnsLeft > 0) {
        _spawnedTank = std::make_shared<PlayerTank>(_position, _spawnerNum);
        game.addObject(_spawnedTank);
        --_spawnsLeft;
      }
    }
    else {
      return;
    }
  }

  // Deleting destroyed tank
  if (_spawnedTank != nullptr && _spawnedTank->isDestroyed()) {
    _spawnedTank = nullptr;
    _animationStartTime = game.getTime() + 64.0 / 60;
  }
}
