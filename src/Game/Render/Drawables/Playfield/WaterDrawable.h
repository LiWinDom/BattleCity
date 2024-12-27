#pragma once

#include "../IDrawable.h"

class WaterDrawable : public IDrawable {
 public:
  WaterDrawable();

  void update(const std::shared_ptr<IObject>& object) override;
};
