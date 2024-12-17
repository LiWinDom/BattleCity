#pragma once

#include "IObject.h"
#include "ITank.h"

class TankSpawner : public IObject {
 public:
  TankSpawner(const sf::Vector2f& position, const ObjectType spawnObject, const uint8_t spawnerNum);

  uint8_t getState() const override;

  void think(Game& game, const Event& event) override;

 private:
  ObjectType _spawnObject;
  uint8_t _spawnerNum;
  uint8_t _currentFrame;

  // Only for players
  uint8_t _spawnsLeft = 4;
  std::shared_ptr<ITank> _spawnedTank;
  float _animationStartTime = -1;
};
