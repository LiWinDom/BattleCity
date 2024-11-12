#pragma once

#include "IObject.h"

class Bullet : public IObject {
 public:
  Bullet(const sf::Vector2f& position, const ObjectRotation& rotation, const bool isFast = false);

  uint8_t getState() const override;

  void think(std::vector<std::shared_ptr<IObject>>& objects, const sf::Clock& globalClock, const Event& event) override;

 protected:
  ObjectRotation _rotation;
  bool _isFast;
};
