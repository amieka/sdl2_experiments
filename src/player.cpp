#include "player.h"

void Player::Init() { player_action = new PlayerAction(); }

// SDL_Rect Player::GetBounds() const { return; }
bool Player::CanCollide(SDL_Rect other) { return false; }

void Player::Move() {
  if (move_dir[0]) {
    pos_x -= VELX;
    if (pos_x < 0) {
      pos_x = 0;
    }
  }
  if (move_dir[1]) {
    pos_x += VELX;
    if (pos_x + width > SCREEN_WIDTH / 2) {
      pos_x = SCREEN_WIDTH / 2;
    }
  }
}

void Player::Render(int camera_x, int camera_y) {
  Uint32 ticks = SDL_GetTicks();
  SDL_RendererFlip flip = SDL_FLIP_NONE;
  if ((move_dir[0]) == 1 || (move_dir[1]) == 0) {
    flip = SDL_FLIP_VERTICAL;
  }
  SDL_Rect t;
  SDL_Rect dest;
  if (player_state == 0) {
    // render idle
    Uint32 sprite_idx = (ticks / 100) % 11;

    dest.x = pos_x;
    dest.y = pos_y;

    t.x = IdleState[sprite_idx][0] - camera_x;
    t.y = IdleState[sprite_idx][1];
    t.w = dest.w = width = IdleState[sprite_idx][2];
    t.h = dest.h = height = IdleState[sprite_idx][3];

  } else {
    // render walking
    Uint32 sprite_idx = (ticks / 100) % 7;
    dest.x = pos_x;
    dest.y = pos_y;
    t.x = WalkingState[sprite_idx][0] - camera_x;
    t.y = WalkingState[sprite_idx][1];
    t.w = dest.w = width = WalkingState[sprite_idx][2];
    t.h = dest.h = height = WalkingState[sprite_idx][3];
  }

  SDL_Point* center = NULL;

  SDL_RenderCopyEx(current_renderer, current_texture, &t, &dest, 0.00, center,
                   flip);
}

void Player::Render() {
  Uint32 ticks = SDL_GetTicks();
  SDL_Rect t;
  SDL_Rect dest;
  SDL_RendererFlip flip = SDL_FLIP_NONE;
  if ((move_dir[0]) == 1 || (move_dir[1]) == 0) {
    flip = SDL_FLIP_HORIZONTAL;
  }
  if (player_state == 0) {
    // render idle
    Uint32 sprite_idx = (ticks / 100) % 11;

    dest.x = pos_x;
    dest.y = pos_y;

    t.x = IdleState[sprite_idx][0];
    t.y = IdleState[sprite_idx][1];
    t.w = dest.w = width = IdleState[sprite_idx][2];
    t.h = dest.h = height = IdleState[sprite_idx][3];

    // SDL_RenderCopy(current_renderer, current_texture, &t, &dest);

  } else {
    // render walking
    Uint32 sprite_idx = (ticks / 100) % 7;
    dest.x = pos_x;
    dest.y = pos_y;
    t.x = WalkingState[sprite_idx][0];
    t.y = WalkingState[sprite_idx][1];
    t.w = dest.w = width = WalkingState[sprite_idx][2];
    t.h = dest.h = height = WalkingState[sprite_idx][3];
    // SDL_RenderCopy(current_renderer, current_texture, &t, &dest);
  }

  SDL_Point* center = NULL;

  SDL_RenderCopyEx(current_renderer, current_texture, &t, &dest, 0.00, center,
                   flip);
}

void Player::SetTexture(SDL_Texture* texture) { current_texture = texture; }

void Player::SetState(PlayerState state) { player_state = state; }

int Player::GetX() const { return pos_x; }

int Player::GetY() const { return pos_y; }

int Player::GetWidth() const { return width; }

int Player::GetHeight() const { return height; }

void Player::Update(SDL_Event event) {
  switch (event.type) {
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
        case SDLK_LEFT:
          move_dir[0] = 1;
          SetState(WALKING);
          break;
        case SDLK_RIGHT:
          SetState(WALKING);
          move_dir[1] = 1;
          break;
      }
      break;
    case SDL_KEYUP:

      switch (event.key.keysym.sym) {
        case SDLK_LEFT:
          move_dir[0] = 0;
          SetState(IDLE);
          break;
        case SDLK_RIGHT:
          move_dir[1] = 0;
          SetState(IDLE);
          break;
      }
      break;
    default:
      break;
  }

  // walking_sprite_idx = (walking_sprite_idx + 1) % 7;
}

bool* Player::ScrollDir() { return move_dir; }
void Player::Update() { Move(); }