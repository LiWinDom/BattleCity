#pragma once

#include <memory>

#include "../Event.h"
#include "../Objects/NetworkObject.h"

namespace Serializer {
  size_t getObjectSize();
  std::shared_ptr<uint8_t[]> objectToBytes(const std::shared_ptr<IObject>& object);
  std::shared_ptr<NetworkObject> bytesToObject(const std::shared_ptr<uint8_t[]>& bytes);

  std::shared_ptr<uint8_t[]> eventToBytes(const Event& event);
  Event bytesToEvent(const std::shared_ptr<uint8_t[]>& player1, const std::shared_ptr<uint8_t[]>& player2);
};
