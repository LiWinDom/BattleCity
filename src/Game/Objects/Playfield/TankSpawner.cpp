#include "TankSpawner.h"

#include <exception>
#include <limits>

#include "../Tank/EnemyTank.h"
#include "../Tank/PlayerTank.h"

TankSpawner::TankSpawner(const sf::Vector2f& position, const ObjectType spawnObject, const uint8_t spawnerNum) :
IObject(ObjectType::Spawner, position, {16, 16}), _spawnObject(spawnObject), _spawnerNum(spawnerNum) {
  if (_spawnObject != ObjectType::PlayerTank && _spawnObject != ObjectType::EnemyTank) {
    throw std::invalid_argument("spawnObject expected to be PlayerTank or EnemyTank");
  }
  _collision = false;
  _nextTankNum = _spawnerNum;
}

ObjectType TankSpawner::getSpawnObject() const {
  return _spawnObject;
}

uint8_t TankSpawner::getState() const {
  return _currentFrame;
}

void TankSpawner::think(Game& game, const Event &event) {
  if (_animationStartTime == -1) {
    // Game start
    if (_spawnObject == ObjectType::PlayerTank) {
      _animationStartTime = game.getTime();
    }
    else {
      _animationStartTime = game.getTime() + game.getPeriod() * _spawnerNum;
    }
  }

  // Waiting for next spawn
  if (_animationStartTime > game.getTime()) {
    return;
  }
  // Animation
  if (_animationStartTime + 64.0 / 60 > game.getTime()) {
    if (_frameChangeTime == -1) {
      _frameChangeTime = game.getTime();
      _currentFrame = 0;
    }
    while (_frameChangeTime + 1.0 / 12 < game.getTime()) {
      _currentFrame = (_currentFrame + 1) % 6;
      _frameChangeTime += 1.0 / 12;
    }
    return;
  }

  // Spawning
  _frameChangeTime = -1;
  _currentFrame = -1;

  if (_spawnObject == ObjectType::PlayerTank) {
    if (_spawnedTank == nullptr) {
      if (_spawnsLeft == 0) {
        _desytroyed = true;
        return;
      }
      _spawnedTank = std::make_shared<PlayerTank>(_position, _spawnerNum);
      game.addObject(_spawnedTank);
      --_spawnsLeft;
    }
  }
  else {
    bool hasBonus = false;
    if (_nextTankNum == 3 || _nextTankNum == 10 || _nextTankNum == 17) {
      hasBonus = true;
    }
    game.addObject(std::make_shared<EnemyTank>(_position, game.getTanks()[_nextTankNum], hasBonus));
    _animationStartTime += game.getPeriod() * 3;
    _nextTankNum += 3;
    if (_nextTankNum >= game.getTanks().size()) {
      _desytroyed = true;
    }
  }

  // Deleting destroyed tank
  if (_spawnedTank != nullptr && _spawnedTank->isDestroyed()) {
    _spawnedTank = nullptr;
    _animationStartTime = game.getTime() + 64.0 / 60;
  }
}
