#ifndef EVENT_DISPATCHER
#define EVENT_DISPATCHER

#include <SDL2/SDL.h>
#include <SDL_image.h>

#include <vector>

#include "event_observer.h"

class EventDispatcher {
  std::vector<EventObserver *> observers;

 public:
  void Attach(EventObserver *observer);

  void Notify(SDL_Event e);
  void Notify();
};

#endif