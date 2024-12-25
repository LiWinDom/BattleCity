#pragma once

#include "../IDrawable.h"

class GameOverDrawable : public IDrawable {
 public:
  GameOverDrawable();

  void update(const std::shared_ptr<IObject>& object) override;
};
