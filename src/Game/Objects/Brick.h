#pragma once

#include "IBlock.h"

class Brick : public IBlock {
 public:
  Brick(const sf::Vector2f& position);

  uint8_t getState() const override;

  void destroy(std::vector<std::shared_ptr<IObject>> &objects, const sf::Clock &globalClock, const ObjectRotation bulletRotation) override;

 private:
  uint8_t _state = 15;
};
