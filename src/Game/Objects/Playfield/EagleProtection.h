#pragma once

#include "Brick.h"
#include "Wall.h"

class EagleProtection : public Brick, public Wall {
 public:
  EagleProtection(const sf::Vector2f& position);

  uint8_t getState() const override;

  void addProtection(Game& game, float time = 20);

  void removeProtection(Game& game, float time = 20);

  void think(Game& game, const Event& event) override;

  void destroy(Game& game, const ObjectRotation& bulletRotation) override;

 private:
  float _stateUntil = -1;
  uint8_t _protectionState = 1;
};
