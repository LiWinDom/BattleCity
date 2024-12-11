#pragma

#include "ITank.h"

class EnemyTank : public ITank {
 public:
  EnemyTank(const sf::Vector2f& position, const uint8_t tankType);

  void think(Game& game, const Event& event) override;

 private:
  void changeDirection(Game& game);
  void rotateClockwise();
  void rotateCounterClockwise();

  Event _event;
};
