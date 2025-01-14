#pragma once

#include <cstdint>

enum class ObjectRotation : uint8_t {
  Up = 0,
  Left = 1,
  Down = 2,
  Right = 3,
};

enum class ObjectType : uint8_t {
  None = 0,
  Border = 1,
  Brick = 2,
  Wall = 3,
  Bush = 4,
  Water = 5,
  Eagle = 6,
  EagleProtection = 7,
  Spawner = 10,
  PlayerTank = 11,
  EnemyTank = 12,
  TankProtection = 15,
  Bullet = 20,
  Explosion = 30,
  Bonus = 40,
  // Interface objects
  GameOver = 101,
  LeftTanks = 102,
  PlayerLives = 103,
  StageNumber = 104,
  // Service
  NewStage = 254,
  NetworkTerminator = 255,
};
