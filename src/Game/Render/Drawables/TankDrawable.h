#pragma once

#include "IDrawable.h"

class TankDrawable : public IDrawable {
 public:
  TankDrawable();

  void update(const std::shared_ptr<IObject>& object) override;
};
