#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include <SDL_image.h>

#include <string>
#include <vector>

#include "common.h"
#include "texture.h"

struct Entity {
  int x;
  int y;
  int w;
  int h;
  int tid;
  int velx;
  int vely;
  SDL_Texture* texture;

  int GetX() const;
  int GetY() const;
  SDL_Texture* GetTexture() const;
  EntityType item_type;
  CurrentState current_state;
  SDL_Renderer* current_renderer;
  std::vector<Texture> layers;
  void Init();
  void Blit();
  void Move();
  void Render(int cam_x, int cam_y);
  void UpdateState(SDL_Event e, CurrentState updated_state);
  Entity() {}
  Entity(EntityType obj_type, int pos_x, int pos_y, int width, int height,
         int texture_id, SDL_Renderer* renderer) {
    item_type = obj_type;
    x = pos_x;
    y = pos_y;
    velx = 0;
    vely = 0;
    w = width;
    h = height;
    tid = texture_id;
    current_renderer = renderer;
    current_state = STILL;
    Init();
  }
};

#endif