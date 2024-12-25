#pragma once

#include "../IMovable.h"

class GameOver : public IMovable {
 public:
  GameOver();

  void think(Game& game, const Event& event) override;
};
