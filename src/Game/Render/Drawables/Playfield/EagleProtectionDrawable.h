#pragma once

#include "../IDrawable.h"

class EagleProtectionDrawable : public IDrawable {
 public:
  EagleProtectionDrawable();

  void update(const std::shared_ptr<IObject>& object) override;
};
