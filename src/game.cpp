#define FPS 60.00

#include "game.h"

#include "object.h"
#include "player.h"
#include "scene.h"
#include "texture.h"

void Game::AnimatePlayer() {
  // get tick
  // Uint32 ticks = SDL_GetTicks();
  // Uint32 sprite = (ticks / 100) % 7;
  // SDL_Rect srcrect = {0, 0, 32, 64};
  // SDL_Rect dstrect = {10, 10, 32, 64};
  // SDL_Texture* t_texture = player_textures[sprite];
  // SDL_RenderCopy(renderer, t_texture, &srcrect, &dstrect);

  if (player_walking != NULL) {
    player_walking->Render(50, 50);
  }
  if (player_idle != NULL) {
    player_idle->Render(300, 300);
  }
}

void Game::Init() {
  IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
  x = 0;
  y = 0;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "Failed to initialize the SDL2 library\n";
    return;
  }

  // init window
  window = SDL_CreateWindow("SDL2 Scroll Animation", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, current_scene.width,
                            current_scene.height, 0);

  // init renderer
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void Game::CreateScene() { current_scene.LoadEntities(renderer); }

void Game::UpdateScene(SDL_Event e) {
  // update game state for all the entities
  current_scene.UpdateOnEvent(e);
}

void Game::PrepareScene() {
  SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
  SDL_RenderClear(renderer);
}

void Game::PresentScene() {
  current_scene.RenderBackground();
  SDL_RenderPresent(renderer);
  SDL_UpdateWindowSurface(window);
}

void Game::HandleInput() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      exit(0);
    }
    UpdateScene(event);
  }
}