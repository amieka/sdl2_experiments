
#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <string.h>

#include <vector>

#include "entity.h"

struct Scene {
  int width;
  int height;
  std::vector<Entity> entities;
  void LoadEntities(SDL_Renderer* renderer);
  std::vector<Entity> GetEntities() const;
  void Init();
  void Blit();
  void Update(SDL_Event e);
  Scene() { Init(); }
};

#endif