#pragma once

#include "../IObject.h"
#include "../Tank/ITank.h"
#include "../Interface/PlayerLives.h"

class TankSpawner : public IObject {
 public:
  TankSpawner(const sf::Vector2f& position, const ObjectType spawnObject, const uint8_t spawnerNum);

  ObjectType getSpawnObject() const;

  uint8_t getState() const override;

  uint8_t getSpawnerNum() const;

  void addLife();

  void think(Game& game, const Event& event) override;

 private:
  ObjectType _spawnObject;
  uint8_t _spawnerNum;
  float _animationStartTime = -1;
  float _frameChangeTime = -1;
  uint8_t _currentFrame = -1;

  // Only for players
  uint8_t _spawnsLeft = 3;
  std::shared_ptr<ITank> _spawnedTank;
  std::shared_ptr<PlayerLives> _livesIndicator = nullptr;

  // Only for enemies
  uint8_t _nextTankNum;
};
