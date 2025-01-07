#pragma once

#include "../IDrawable.h"

class BonusDrawable : public IDrawable {
 public:
  BonusDrawable();

  void update(const std::shared_ptr<IObject>& object) override;
};
