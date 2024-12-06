#pragma

#include "ITank.h"

class PlayerTank : public ITank {
 public:
  PlayerTank(const sf::Vector2f& position, const bool playerNum = 0);

  void think(Game& game, const Event& event) override;
};
