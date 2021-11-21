
#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL.h>
#include <SDL_image.h>

#include <string>
#include <vector>

#include "entity.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 483

#define LEVEL_WIDTH 1200
#define LEVEL_HEIGHT 960

enum ScrollDirection { DIR_LEFT, DIR_RIGHT };

struct Texture {
  SDL_Renderer* current_renderer;
  SDL_Texture* current_texture;
  int width, height;
  void Render(int x, int y);
  void Init(std::string texture_path);
  int GetWidth() const;
  int GetHeight() const;
  Texture(std::string texture_name, SDL_Renderer* renderer) {
    // bad idea ? too many copies
    current_renderer = renderer;
    Init(texture_name);
  }
};

struct Background {
  std::vector<Texture> layers;
  int scrolling_offset;
  ScrollDirection scrolling_direction;
  void Update(SDL_Event e);
  void AddLayer(std::string texture_path, SDL_Renderer* renderer);
  void Init();
  Background() { Init(); }
};

struct Scene {
  int width;
  int height;
  int scrolling_offset;
  std::vector<Entity> entities;
  std::vector<SDL_Texture*> backgrounds;
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