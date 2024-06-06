#ifndef BATTLECITY_PLAYERTANK_H
#define BATTLECITY_PLAYERTANK_H

#include "ITank.h"

class PlayerTank : public ITank {
 public:
  PlayerTank(const sf::Vector2f& position);

  void think(const std::vector<std::shared_ptr<IObject>>& objects, uint16_t index, const sf::Clock& globalClock, const Event& event) override;
};


#endif //BATTLECITY_PLAYERTANK_H
