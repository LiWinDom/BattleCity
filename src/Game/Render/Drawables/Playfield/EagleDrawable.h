#pragma once

#include "../IDrawable.h"

class EagleDrawable : public IDrawable {
 public:
  EagleDrawable();

  void update(const std::shared_ptr<IObject>& object) override;
};
