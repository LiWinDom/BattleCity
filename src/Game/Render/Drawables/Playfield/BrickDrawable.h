#pragma once

#include "../IDrawable.h"

class BrickDrawable : public IDrawable {
 public:
  BrickDrawable();

  void update(const std::shared_ptr<IObject>& object) override;
};
