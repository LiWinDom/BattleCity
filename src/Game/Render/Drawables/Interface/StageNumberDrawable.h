#pragma once

#include "../IDrawable.h"

class StageNumberDrawable : public IDrawable {
 public:
  StageNumberDrawable();

  void update(const std::shared_ptr<IObject>& object) override;
};
