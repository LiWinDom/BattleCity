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
  Protection = 7,
  Spawner = 10,
  PlayerTank = 11,
  EnemyTank = 12,
  Bullet = 20,
  Explosion = 30,
};
