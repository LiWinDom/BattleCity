#pragma

#include "ITank.h"

class PlayerTank : public ITank {
 public:
  PlayerTank(const sf::Vector2f& position);

  void think(std::vector<std::shared_ptr<IObject>>& objects, const sf::Clock& globalClock, const Event& event) override;
};
