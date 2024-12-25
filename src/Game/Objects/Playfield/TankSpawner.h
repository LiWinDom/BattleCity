#pragma once

#include "../IObject.h"
#include "../Tank/ITank.h"

class TankSpawner : public IObject {
 public:
  TankSpawner(const sf::Vector2f& position, const ObjectType spawnObject, const uint8_t spawnerNum);

  ObjectType getSpawnObject() const;

  uint8_t getState() const override;

  void think(Game& game, const Event& event) override;

 private:
  ObjectType _spawnObject;
  uint8_t _spawnerNum;
  float _animationStartTime = -1;
  float _frameChangeTime = -1;
  uint8_t _currentFrame = -1;

  // Only for players
  uint8_t _spawnsLeft = 4;
  std::shared_ptr<ITank> _spawnedTank;

  // Only for enemies
  uint8_t _nextTankNum;
};
