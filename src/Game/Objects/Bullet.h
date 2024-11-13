#pragma once

#include "IMovable.h"

class Bullet : public IMovable {
 public:
  Bullet(const sf::Vector2f& tankPosition, const ObjectRotation& rotation, const bool isFast = false);

  uint8_t getState() const override;

  void think(std::vector<std::shared_ptr<IObject>>& objects, const sf::Clock& globalClock, const Event& event) override;
};
