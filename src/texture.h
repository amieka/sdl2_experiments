
#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL_image.h>

#include <string>
#include <vector>

#include "common.h"

struct Layer {
  SDL_Rect rect;
  int scroll_speed;
  int scrolling_offset;
};

struct Texture {
  SDL_Renderer* current_renderer;
  SDL_Texture* current_texture;

  SDL_Rect layer_rect;
  int width, height;

  void RenderWithOffset(int x, int y);
  void Render();
  void Init(std::string texture_path);
  void UpdateScrollOffset(SDL_Event e);
  int GetWidth() const;
  int GetHeight() const;
  SDL_Texture* GetTexture() const;
  SDL_Texture* GetTexture(int x, int y, int w, int h) const;

  int scroll_offset;
  int scroll_speed;
  ScrollDirection scroll_direction;

  Texture(std::string texture_name, SDL_Renderer* renderer) {
    // bad idea ? too many copies
    current_renderer = renderer;
    scroll_speed = 0;
    scroll_offset = 0;
    scroll_direction = DIR_LEFT;
    Init(texture_name);
  }

  Texture(std::string texture_name, SDL_Renderer* renderer, int speed) {
    // bad idea ? too many copies
    current_renderer = renderer;
    scroll_speed = speed;
    scroll_offset = 0;
    scroll_direction = DIR_LEFT;
    Init(texture_name);
  }
};

#endif