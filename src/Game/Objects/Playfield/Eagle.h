#pragma once

#include "../IObject.h"

class Eagle : public IObject {
 public:
  Eagle(const sf::Vector2f& position);

  uint8_t getState() const override;

  void destroy(Game& game, const ObjectRotation& bulletRotation = ObjectRotation::Up, const bool powerfulBullet = false) override;

 private:
  bool _state = false;
};
