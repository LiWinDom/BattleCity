#pragma once

#include "IBlock.h"

class Water : public IBlock {
 public:
  Water(const sf::Vector2f& position);

  uint8_t getState() const override;

  void think(Game& game, const Event& event) override;

 private:
  uint8_t _currentFrame;
};
