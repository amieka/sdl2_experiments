#include "player.h"

void Player::Init() {}

void Player::Move() {
  if (move_dir[0]) {
    pos_x -= VELX;
    if (pos_x < 0) {
      pos_x = 0;
    }
  }
  if (move_dir[1]) {
    pos_x += VELX;
    if (pos_x > SCREEN_WIDTH) {
      pos_x = SCREEN_WIDTH;
    }
  }
}

void Player::Render() {
  Uint32 ticks = SDL_GetTicks();

  if (player_state == 0) {
    // render idle
    Uint32 sprite_idx = (ticks / 100) % 11;
    SDL_Rect t;
    SDL_Rect dest;
    dest.x = pos_x;
    dest.y = pos_y;

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
    dest.x = pos_x;
    dest.y = pos_y;
    t.x = WalkingState[sprite_idx][0];
    t.y = WalkingState[sprite_idx][1];
    t.w = dest.w = WalkingState[sprite_idx][2];
    t.h = dest.h = WalkingState[sprite_idx][3];
    SDL_RenderCopy(current_renderer, current_texture, &t, &dest);
  }
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
    // Uint32 sprite_idx = (ticks / 100) % 7;
    SDL_Rect t;
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    t.x = WalkingState[walking_sprite_idx][0];
    t.y = WalkingState[walking_sprite_idx][1];
    t.w = dest.w = WalkingState[walking_sprite_idx][2];
    t.h = dest.h = WalkingState[walking_sprite_idx][3];
    SDL_RenderCopy(current_renderer, current_texture, &t, &dest);
  }
}

void Player::SetState(PlayerState state) { player_state = state; }

int Player::GetX() const { return 1; }

int Player::GetY() const { return 2; }

void Player::Update(SDL_Event event) {
  switch (event.type) {
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
        case SDLK_LEFT:
          move_dir[0] = 1;
          player_state = WALKING;
          // velx -= VELX;

          break;
        case SDLK_RIGHT:
          player_state = WALKING;
          move_dir[1] = 1;
          // velx += VELX;
          break;
      }
      break;
    case SDL_KEYUP:

      switch (event.key.keysym.sym) {
        case SDLK_LEFT:
          move_dir[0] = 0;
          player_state = IDLE;
          break;
        case SDLK_RIGHT:
          move_dir[1] = 0;
          player_state = IDLE;
          break;
      }
      break;
    default:
      break;
  }

  // walking_sprite_idx = (walking_sprite_idx + 1) % 7;
}
void Player::Update() { Render(); }