#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL2/SDL.h>
#include <SDL_image.h>

#include <string>
#include <vector>

#include "common.h"
#include "texture.h"

struct Background {
  std::vector<Texture> layers;
  int scrolling_offset;
  ScrollDirection scrolling_direction;
  void Update(SDL_Event e);
  void AddLayer(std::string texture_path, SDL_Renderer* renderer,
                int scroll_speed);
  void Init();
  void Render();
  Background() { Init(); }
};

#endif