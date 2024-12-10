#pragma

#include "ITank.h"

class EnemyTank : public ITank {
 public:
  EnemyTank(const sf::Vector2f& position, const bool playerNum = 0);

  void think(Game& game, const Event& event) override;
};
