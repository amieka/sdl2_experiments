#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL2/SDL.h>
#include <SDL_image.h>

#include <string>
#include <vector>

#include "common.h"
#include "event_observer.h"
#include "texture.h"

struct Background {
  std::vector<Texture> layers;
  int scrolling_offset;
  SDL_Texture* current_texture;
  ScrollDirection scrolling_direction;
  void UpdateScrollOffset();
  void Update(SDL_Event e);
  void SetTexture(SDL_Texture* texture);
  void AddLayer(std::string texture_path, SDL_Renderer* renderer,
                int scroll_speed);
  void AddLayer(SDL_Rect rect, SDL_Renderer* renderer, int scroll_speed);
  void Init();
  void Render();
  void Render(int x, int y, bool* scroll_dir);
  Background() { Init(); }
};

#endif