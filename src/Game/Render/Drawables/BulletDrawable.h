#pragma once

#include "IDrawable.h"

class BulletDrawable : public IDrawable {
 public:
  BulletDrawable();

  void update(const std::shared_ptr<IObject>& object) override;
};
