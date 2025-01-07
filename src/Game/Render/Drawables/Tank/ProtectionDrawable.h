#pragma once

#include "../IDrawable.h"

class ProtectionDrawable : public IDrawable {
 public:
  ProtectionDrawable();

  void update(const std::shared_ptr<IObject>& object) override;
};
