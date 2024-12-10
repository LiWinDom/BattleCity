#include "Explosion.h"

Explosion::Explosion(const sf::Vector2f& position, const bool isBig) :
    IObject(ObjectType::Explosion, position, {16, 16}), _isBig(isBig) {
  _collision = false;
}

uint8_t Explosion::getState() const {
  return _currentFrame;
}

void Explosion::think(Game &game, const Event &event) {
  // Small explosion: 0 -> 1 -> 2, 3 frames per frame (0.05 sec)
  // Big explosion: 0 -> 1 -> 2 -> 3 -> 4 -> 2, 6 frames per frame (0.1 sec)
  if (_lastFrameChange == -1) {
    _lastFrameChange = game.getTime();
  }

  double frameTime = _isBig ? 0.1 : 0.05;
  uint totalFrames = _isBig ? 6 : 3;

  while (game.getTime() >= _lastFrameChange + frameTime) {
    _lastFrameChange += frameTime;
    ++_playedFrames;
    ++_currentFrame;
    if (_playedFrames >= totalFrames) {
      _desytroyed = true;
      return;
    }
    if (_currentFrame >= 5) {
      _currentFrame = 2;
    }
  }
}
