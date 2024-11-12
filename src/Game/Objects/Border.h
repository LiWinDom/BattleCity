#pragma once

#include "IObject.h"

class Border : public IObject {
 public:
  Border(uint8_t borderNum);

  uint8_t getState() const override;

  void think(std::vector<std::shared_ptr<IObject>> &objects, const sf::Clock &globalClock, const Event &event) override;
};
