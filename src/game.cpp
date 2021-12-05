#define FPS 60.00

#include "game.h"

#include <iostream>

#include "object.h"
#include "player.h"
#include "scene.h"
#include "texture.h"

void Game::Init() {
  current_scene = new Scene();
  IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "Failed to initialize the SDL2 library\n";
    return;
  }

  // init window
  window = SDL_CreateWindow("SDL2 Scroll Animation", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, current_scene->width,
                            current_scene->height, 0);

  // init renderer
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void Game::CreateScene() {
  Init();
  current_scene->LoadEntities(renderer);
}

void Game::UpdateScene(SDL_Event e) {
  // update game state for all the entities
  current_scene->Update(e);
}

void Game::PrepareScene() {
  SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
  SDL_RenderClear(renderer);
}

void Game::PresentScene() {
  current_scene->RenderBackground();
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