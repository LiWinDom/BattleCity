#pragma once

#include "IDrawable.h"

class BlockDrawable : public IDrawable {
 public:
  BlockDrawable();

  void update(const std::shared_ptr<IObject>& object) override;
};
