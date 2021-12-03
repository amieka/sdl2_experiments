
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <string.h>

#include <iostream>
#include <vector>

#include "src/game.h"

int main() {
  Scene scene;

  Game game(scene);
  game.CreateScene();

  while (1) {
    game.PrepareScene();

    game.PresentScene();

    game.HandleInput();

    SDL_Delay(16);
  }
  return 0;
}
