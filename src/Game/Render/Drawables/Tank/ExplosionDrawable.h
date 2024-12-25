#pragma once

#include "../IDrawable.h"

class ExplosionDrawable : public IDrawable {
 public:
  ExplosionDrawable();

  void update(const std::shared_ptr<IObject>& object) override;
};
