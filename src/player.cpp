#include "player.h"

void Player::Init() {
  // fill out the layers
  for (int i = 0; i < 2; i++) {
    // int* action[4] = StateLayers[i];
  }
}

void Player::Render() {
  // do nothing yet
}

void Player::SetTexture(SDL_Texture* texture) { current_texture = texture; }

void Player::Render(int x, int y) {
  // render at a certain x,y pos
  printf("method called with : %d, %d \n", x, y);
  Uint32 ticks = SDL_GetTicks();
  if (player_state == 0) {
    // render idle
    Uint32 sprite_idx = (ticks / 100) % 11;
    SDL_Rect t;
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;

    t.x = IdleState[sprite_idx][0];
    t.y = IdleState[sprite_idx][1];
    t.w = dest.w = IdleState[sprite_idx][2];
    t.h = dest.h = IdleState[sprite_idx][3];
    // printf("sprite:idle idx: %d , pos_x: %d, pos_y: %d", sprite_idx, t.x,
    // t.y);
    SDL_RenderCopy(current_renderer, current_texture, &t, &dest);

  } else {
    // render walking
    Uint32 sprite_idx = (ticks / 100) % 7;
    SDL_Rect t;
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    t.x = WalkingState[sprite_idx][0];
    t.y = WalkingState[sprite_idx][1];
    t.w = dest.w = WalkingState[sprite_idx][2];
    t.h = dest.h = WalkingState[sprite_idx][3];
    SDL_RenderCopy(current_renderer, current_texture, &t, &dest);
  }
}
void Player::Move(SDL_Event e) {
  // do nothing yet
  player_state = WALKING;
}

void Player::SetState(PlayerState state) { player_state = state; }

int Player::GetX() const { return 1; }

int Player::GetY() const { return 2; }