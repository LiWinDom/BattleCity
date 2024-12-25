#pragma once

#include "../IObject.h"

class Explosion : public IObject {
 public:
  Explosion(const sf::Vector2f& position, const bool isBig);

  uint8_t getState() const override;

  void think(Game& game, const Event& event) override;

 private:
  bool _isBig;
  uint8_t _currentFrame = 0;
  uint8_t _playedFrames = 0;
  float _lastFrameChange = -1;
};
