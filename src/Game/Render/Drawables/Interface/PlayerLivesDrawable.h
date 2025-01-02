#pragma once

#include "../IDrawable.h"

class PlayerLivesDrawable : public IDrawable {
 public:
  PlayerLivesDrawable();

  void update(const std::shared_ptr<IObject>& object) override;
};
