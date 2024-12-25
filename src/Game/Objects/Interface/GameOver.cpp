#include "GameOver.h"

GameOver::GameOver() :
IMovable(ObjectType::GameOver, {88, 208}, {32, 8}, ObjectRotation::Up, 60) {
  _collision = false;
}

void GameOver::think(Game& game, const Event &event) {
  move(game);
  if (_position.y == 96) {
    _speed = 0;
  }
}
