
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <string.h>

#include <iostream>
#include <vector>
#define FPS 60.00

#include "src/scene.h"
#define LEVEL_WIDTH 1200
#define LEVEL_HEIGHT 480
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 483

struct Game {
  SDL_Window* window;
  SDL_Renderer* renderer;
  Scene current_scene;
  SDL_Texture* texture;
  SDL_Rect camera_rect;
  int x, y;

  void Init();
  void PrepareScene();
  void PresentScene();
  void HandleInput();
  void UpdateBackground();
  void CreateScene();
  void UpdateScene(SDL_Event e);
  void LoadTexture();
  Game(Scene scene) {
    current_scene = scene;
    Init();
  }
};

void Game::Init() {
  IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
  x = 0;
  y = 0;
  camera_rect.x = 0;
  camera_rect.y = 0;
  camera_rect.w = SCREEN_WIDTH;
  camera_rect.h = SCREEN_HEIGHT;
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

void Game::CreateScene() {
  current_scene.LoadEntities(renderer);
}

void Game::UpdateScene(SDL_Event e) {
  // update game state for all the entities
  current_scene.Update(e);
}

void Game::LoadTexture() {
  SDL_Rect dest;
  std::string asset_path = "../assets/_02_trees_bushes.png";
  texture = IMG_LoadTexture(renderer, asset_path.c_str());
  dest.x = 0;
  dest.y = 0;
  dest.w = 640;
  dest.h = 483;
  SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void Game::UpdateBackground() {
  printf("background updated with pos, %d %d", camera_rect.x, camera_rect.y);
  SDL_RenderCopy(renderer, texture, NULL, &camera_rect);
}

void Game::PrepareScene() {
  SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
  SDL_RenderClear(renderer);
}

void Game::PresentScene() {
  LoadTexture(); // loads the background
  current_scene.Blit(); // renders all the entities
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

int main() {
  Scene scene;
  scene.width = 640;   // 2048;
  scene.height = 483;  // 1546;

  Game game(scene);
  game.CreateScene();

  while (1) {
    game.PrepareScene();

    game.PresentScene();

    game.HandleInput();

    // game.DrawRect();

    SDL_Delay(16);
  }
  return 0;
}
