#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include <SDL_image.h>

#define VELX 10

enum EntityType { PLAYER, BACKGROUND };

enum CurrentState { STILL, RUNNING };

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
  void Init();
  void Blit();
  void Move();
  void Render();
  void UpdateState(SDL_Event e,CurrentState updated_state);
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
    current_state = CurrentState::STILL;
    Init();
  }
};

#endif