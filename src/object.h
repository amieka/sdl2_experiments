#ifndef OBJECT_H
#define OBJECT_H

#include <SDL2/SDL.h>
#include <SDL_image.h>

#include <string>

#include "common.h"

class Object {
 public:
  SDL_Texture* root_texture;
  int width, height;
  Object(){};
  Object(std::string texture_name, SDL_Renderer* renderer) {
    std::string asset_path = "../assets/" + texture_name;
    SDL_Surface* texture_surface = IMG_Load(asset_path.c_str());
    SDL_SetColorKey(texture_surface, SDL_TRUE,
                    SDL_MapRGB(texture_surface->format, 0, 0xFF, 0xFF));
    root_texture = SDL_CreateTextureFromSurface(renderer, texture_surface);
    width = texture_surface->w;
    height = texture_surface->h;
    SDL_FreeSurface(texture_surface);
  }
  virtual void Render() {}
  virtual void Move(SDL_Event e) {}
  virtual int GetX() const { return 0; }
  virtual int GetY() const { return 0; }
  virtual ~Object() {}
};

#endif