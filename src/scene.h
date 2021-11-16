
#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL.h>
#include <SDL_image.h>

#include <vector>

#include "entity.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 483

#define LEVEL_WIDTH 1200
#define LEVEL_HEIGHT 960

struct Scene {
  int width;
  int height;
  std::vector<Entity> entities;
  SDL_Rect camera;
  SDL_Renderer* current_renderer;
  std::vector<Entity> GetEntities() const;
  void RenderBackground();
  void LoadEntities(SDL_Renderer* renderer);
  void Init();
  void Blit();
  void Update(SDL_Event e);
  void UpdateCamera(int x, int y, int w, int h);
  Scene() { Init(); }
};

#endif