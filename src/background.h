#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL2/SDL.h>
#include <SDL_image.h>

#include <map>
#include <string>
#include <vector>

#include "common.h"
#include "event_observer.h"
#include "texture.h"

struct Background {
  std::vector<Texture> layers;
  std::vector<Layer> layer_rects;
  int scrolling_offset;
  SDL_Texture* current_texture;
  SDL_Renderer* current_renderer;
  ScrollDirection scrolling_direction;
  void UpdateScrollOffset(SDL_Event event, Layer& current_layer);
  void Update(SDL_Event e);
  void SetTexture(SDL_Texture* texture);
  void SetRenderer(SDL_Renderer* r);
  void AddLayer(std::string texture_path, SDL_Renderer* renderer,
                int scroll_speed);
  void AddLayer(Layer new_layer);
  void Init();
  void Render();
  void RenderLayer(Layer current_layer, int x, int y);
  void Render(int x, int y, bool* scroll_dir);
  Background() { Init(); }
};

#endif