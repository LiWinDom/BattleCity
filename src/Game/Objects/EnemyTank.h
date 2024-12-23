#pragma once

#include "ITank.h"

class EnemyTank : public ITank {
 public:
  EnemyTank(const sf::Vector2f& position, const uint8_t tankType, const bool hasBonus = false);

  uint8_t getState() const override;

  void changeColor(const Game& game);
  void think(Game& game, const Event& event) override;

 private:
  void changeDirection(Game& game);
  void rotateClockwise();
  void rotateCounterClockwise();

  Event _event;

  uint8_t _color = 0b10;
  float _bonusBlinkTime = -1;
};
