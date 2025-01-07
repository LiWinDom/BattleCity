#pragma once

#include "../IDrawable.h"

class TankProtectionDrawable : public IDrawable {
 public:
  TankProtectionDrawable();

  void update(const std::shared_ptr<IObject>& object) override;
};
