#pragma once

#include "../IDrawable.h"

class WallDrawable : public IDrawable {
 public:
  WallDrawable();

  void update(const std::shared_ptr<IObject>& object) override;
};
