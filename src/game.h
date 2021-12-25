#include <SDL2/SDL.h>
#include <SDL_image.h>

#include "scene.h"

struct Game {
  SDL_Window* window;
  SDL_Renderer* renderer;
  Scene* current_scene;
  SDL_Texture* texture;
  int frames_so_far;
  void Init();
  void PrepareScene();
  void PresentScene();
  void HandleInput();
  void CreateScene();
  void UpdateScene(SDL_Event e);
  void ComputeFps();
};