

#include <iostream>

#include "src/game.h"

int main() {
  Game game;
  game.CreateScene();

  while (1) {
    game.PrepareScene();

    game.PresentScene();

    game.HandleInput();

    SDL_Delay(16);
  }
  return 0;
}
