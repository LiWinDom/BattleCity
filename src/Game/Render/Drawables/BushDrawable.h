#pragma once

#include "IDrawable.h"

class BushDrawable : public IDrawable {
 public:
  BushDrawable();

  void update(const std::shared_ptr<IObject>& object) override;
};
