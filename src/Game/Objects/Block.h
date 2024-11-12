#pragma once

#include "IBlock.h"

class Block : public IBlock {
 public:
  Block(const sf::Vector2f& position);

  uint8_t getState() const override;

  void think(const std::vector<std::shared_ptr<IObject>> &objects, const sf::Clock &globalClock, const Event &event) override;
};
