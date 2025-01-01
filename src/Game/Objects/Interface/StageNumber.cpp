#include "StageNumber.h"

StageNumber::StageNumber() : IObject(ObjectType::StageNumber, {216, 184}, {16, 8}) {
  _collision = false;
}

uint8_t StageNumber::getState() const {
  return _state;
}

void StageNumber::think(Game& game, const Event &event) {
  _state = game.getStage();
}
