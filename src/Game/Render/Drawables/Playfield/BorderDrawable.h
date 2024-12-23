#pragma once

#include "../IDrawable.h"

class BorderDrawable : public IDrawable {
 public:
  BorderDrawable();

  void update(const std::shared_ptr<IObject>& object) override;
};
