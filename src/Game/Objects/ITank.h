#pragma once

#include "Bullet.h"
#include "IMovable.h"

class ITank : public IMovable {
 public:
  ITank(ObjectType type, const sf::Vector2f& position);

  uint8_t getState() const override;

  void think(std::vector<std::shared_ptr<IObject>> &objects, const sf::Clock& globalClock, const Event& event) override;

  void shoot(std::vector<std::shared_ptr<IObject>> &objects);

 protected:
  static void snap(float& coordinate);

  bool _wheelState = false;
  uint8_t _maxBullets = 1;
  std::vector<std::shared_ptr<IObject>> _bullets;
};
