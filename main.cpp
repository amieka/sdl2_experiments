
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <string.h>

#include <iostream>
#include <vector>
#define FPS 60.00

#include "src/object.h"
#include "src/player.h"
#include "src/scene.h"

struct Game {
  SDL_Window* window;
  SDL_Renderer* renderer;
  Scene current_scene;
  SDL_Texture* texture;
  int x, y;
  std::vector<SDL_Texture*> player_textures;

  void Init();
  void PrepareScene();
  void PresentScene();
  void HandleInput();
  void UpdateBackground();
  void CreateScene();
  void UpdateScene(SDL_Event e);
  void LoadTexture();
  void AnimatePlayer();
  Game(Scene scene) {
    current_scene = scene;
    Init();
  }
};

void Game::AnimatePlayer() {
  // get tick
  Uint32 ticks = SDL_GetTicks();
  Uint32 sprite = (ticks / 100) % 7;
  SDL_Rect srcrect = {0, 0, 32, 64};
  SDL_Rect dstrect = {10, 10, 32, 64};
  SDL_Texture* t_texture = player_textures[sprite];
  SDL_RenderCopy(renderer, t_texture, &srcrect, &dstrect);
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

  player_textures.clear();
  // load all the player texture here
  Object* root = new Object("data.png", renderer);
  Player* player_idle = new Player(renderer);
  Player* player_walking = new Player(renderer);
  player_walking->SetState(WALKING);
  player_idle->Render(30, 30);
  player_walking->Render(50, 50);
}

void Game::CreateScene() { current_scene.LoadEntities(renderer); }

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

void Game::PrepareScene() {
  SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
  SDL_RenderClear(renderer);
}

void Game::PresentScene() {
  // LoadTexture();         // loads the background
  // current_scene.Blit();  // renders all the entities
  // current_scene.RenderBackground();
  AnimatePlayer();
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
