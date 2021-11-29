#include "event_dispatcher.h"

void EventDispatcher::Attach(EventObserver* obs) { observers.push_back(obs); }

void EventDispatcher::Notify(SDL_Event e) {
  for (auto& observer : observers) {
    observer->Update(e);
  }
}

void EventDispatcher::Notify() {
  for (auto& observer : observers) {
    observer->Update();
  }
}