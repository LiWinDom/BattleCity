#pragma once

#include "../IDrawable.h"

class TankSpawnerDrawable : public IDrawable {
 public:
  TankSpawnerDrawable();

  void update(const std::shared_ptr<IObject>& object) override;
};
