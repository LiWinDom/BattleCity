#pragma once

#include "../IDrawable.h"

class LeftTanksDrawable : public IDrawable {
 public:
  LeftTanksDrawable();

  void update(const std::shared_ptr<IObject>& object) override;
};
