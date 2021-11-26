#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL_image.h>

#include <map>
#include <vector>

#include "common.h"
#include "texture.h"
#define MAX_NUM_IMG_FRAMES 12

// const SDL_Rect StateLayers[4][] = {{SDL_Rect{0, 1449, 21, 33}}};
// extracted from texture packer

const int WalkingState[][4] = {{228, 1449, 21, 33}, {249, 1449, 21, 33},
                               {270, 1449, 21, 33}, {291, 1449, 21, 33},
                               {312, 1449, 21, 33}, {333, 1449, 21, 33},
                               {354, 1449, 21, 33}, {375, 1449, 21, 33}};
const int IdleState[][4] = {
    {0, 1449, 19, 34},   {19, 1449, 19, 34},  {38, 1449, 19, 34},
    {57, 1449, 19, 34},  {76, 1449, 19, 34},  {95, 1449, 19, 34},
    {114, 1449, 19, 34}, {133, 1449, 19, 34}, {152, 1449, 19, 34},
    {171, 1449, 19, 34}, {190, 1449, 19, 34}, {209, 1449, 19, 34}};

class Player {
 private:
  PlayerState player_state;
  SDL_Renderer* current_renderer;
  SDL_Texture* current_texture;
  std::map<int, std::vector<SDL_Rect> > layers_pair;
  float pos_x, pos_y;
  float velx, vely;

 public:
  Player(SDL_Renderer* renderer) {
    current_renderer = renderer;
    velx = vely = 0.00;
    pos_x = pos_y = 0.00;
    player_state = IDLE;
  }
  void Init();
  int GetX() const;
  int GetY() const;
  void SetState(PlayerState state);
  void SetTexture(SDL_Texture* texture);
  void Render();
  void Render(int x, int y);
  void Move(SDL_Event e);
  ~Player() {}
};

#endif