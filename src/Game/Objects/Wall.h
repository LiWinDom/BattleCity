#pragma once

#include "IBlock.h"

class Wall : public IBlock {
 public:
  Wall(const sf::Vector2f& position);

  uint8_t getState() const override;

  void think(std::vector<std::shared_ptr<IObject>> &objects, const sf::Clock &globalClock, const Event &event) override;
};
