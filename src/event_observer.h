#ifndef EVENT_OBSERVER
#define EVENT_OBSERVER

#include <SDL2/SDL.h>

#include <vector>
class EventObserver {
 public:
  EventObserver() {}
  virtual void Update(SDL_Event e) = 0;
  virtual void Update() = 0;
  virtual ~EventObserver() {}
};

#endif