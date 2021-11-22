
#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL.h>
#include <SDL_image.h>

#include <string>
#include <vector>

#include "background.h"
#include "common.h"
#include "entity.h"

struct Scene {
  int width;
  int height;
  int scrolling_offset;
  std::vector<Entity> entities;
  std::vector<SDL_Texture*> backgrounds;
  Background scene_background;
  SDL_Rect camera;
  SDL_Renderer* current_renderer;
  SDL_Texture* current_texture;
  std::vector<Entity> GetEntities() const;
  void RenderBackground();
  void RenderBackgroundInternal(int x, int y);
  void RenderEntities();
  void UpdateScrollingOffsets(int x, int y);
  void LoadEntities(SDL_Renderer* renderer);
  void Init();
  void Blit();
  void Update(SDL_Event e);
  void UpdateCamera(int x, int y, int w, int h);
  Scene() { Init(); }
};

#endif