#ifndef BATTLECITY_EVENT_H
#define BATTLECITY_EVENT_H

struct Event {
  bool up = false;
  bool down = false;
  bool left = false;
  bool right = false;
  bool shoot = false;
  bool esc = false;
};

#endif //BATTLECITY_EVENT_H
