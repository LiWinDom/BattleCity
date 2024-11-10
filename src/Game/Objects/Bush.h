#pragma once

#include "IBlock.h"

class Bush : public IBlock {
 public:
  Bush(const sf::Vector2f& position);

  uint8_t getState() const override;

  void think(const std::vector<std::shared_ptr<IObject>> &objects, uint16_t index, const sf::Clock &globalClock, const Event &event) override;
};
