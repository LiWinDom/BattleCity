#include "Serializer.h"

size_t Serializer::getObjectSize() {
  return 9;
}

std::unique_ptr<uint8_t[]> Serializer::objectToBytes(const std::shared_ptr<IObject> &object) {
  auto data = std::make_unique<uint8_t[]>(getObjectSize());

  data[0] = object->getId() >> 24 & 255;
  data[1] = object->getId() >> 16 & 255;
  data[2] = object->getId() >> 8 & 255;
  data[3] = object->getId() & 255;
  data[4] = static_cast<uint8_t>(object->getType());
  data[5] = object->isDestroyed();
  data[6] = object->getPosition().x;
  data[7] = object->getPosition().y;
  data[8] = object->getState();

  return data;
}

std::shared_ptr<NetworkObject> Serializer::bytesToObject(const std::unique_ptr<uint8_t[]>& bytes) {
  return std::make_shared<NetworkObject>(
      (uint32_t)bytes[0] << 24 | bytes[1] << 16 | bytes[2] << 8 | bytes[3],
      static_cast<ObjectType>(bytes[4]),
      bytes[5],
      bytes[6],
      bytes[7],
      bytes[8]
  );
}

std::unique_ptr<uint8_t[]> Serializer::eventToBytes(const Event &event) {
  auto data = std::make_unique<uint8_t[]>(1);

  data[0] = (event.player1.esc | event.player2.esc) << 7
          | (event.player1.reset | event.player2.reset) << 6
          | (event.player1.up | event.player2.up) << 4
          | (event.player1.left | event.player2.left) << 3
          | (event.player1.down | event.player2.down) << 2
          | (event.player1.right | event.player2.right) << 1
          | (event.player1.shoot | event.player2.shoot);

  return data;
}

Event Serializer::bytesToEvent(const std::unique_ptr<uint8_t[]> &player1, const std::unique_ptr<uint8_t[]>& player2) {
  Event event;

  event.player1.esc =   (player1[0] >> 7) & 1;
  event.player1.reset = (player1[0] >> 6) & 1;
  event.player1.up =    (player1[0] >> 4) & 1;
  event.player1.left =  (player1[0] >> 3) & 1;
  event.player1.down =  (player1[0] >> 2) & 1;
  event.player1.right = (player1[0] >> 1) & 1;
  event.player1.shoot =  player1[0] & 1;

  event.player2.esc =   (player2[0] >> 7) & 1;
  event.player2.reset = (player1[0] >> 6) & 1;
  event.player2.up =    (player2[0] >> 4) & 1;
  event.player2.left =  (player2[0] >> 3) & 1;
  event.player2.down =  (player2[0] >> 2) & 1;
  event.player2.right = (player2[0] >> 1) & 1;
  event.player2.shoot =  player2[0] & 1;

  return event;
}
