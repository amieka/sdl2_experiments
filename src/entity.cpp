#include "entity.h"

// TODO: belongs else where
std::string backgrounds[2] = {"_02_trees_bushes.png", "_02_trees_bushes.png"};

void Entity::Move() {
  x += velx;
  if ((x < 0) || (x + w > 1280)) {
    // Move back
    x -= velx;
  }
}

void Entity::Render(int cam_x, int cam_y) {
  SDL_Rect dest;

  dest.x = x - cam_x;
  dest.y = y;
  dest.w = w;
  dest.h = h;

  SDL_RenderCopy(current_renderer, texture, NULL, &dest);
}

void Entity::UpdateState(SDL_Event event, CurrentState updated_state) {
  current_state = updated_state;
  switch (event.type) {
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
        case SDLK_LEFT:
          if (item_type == 0) {
            velx -= VELX;
          }

          break;
        case SDLK_RIGHT:
          if (item_type == 0) {
            velx += VELX;
          }
          break;
      }
      break;
    case SDL_KEYUP:
      current_state = STILL;
      switch (event.key.keysym.sym) {
        case SDLK_LEFT:
          if (item_type == 0) {
            velx += VELX;
          }

          break;
        case SDLK_RIGHT:
          if (item_type == 0) {
            velx -= VELX;
          }
          break;
      }
      break;
    default:
      break;
  }
}

void Entity::Blit() {
  // copy texture

  // SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
}

void Entity::Init() {}

int Entity::GetX() const { return x; }

int Entity::GetY() const { return y; }

SDL_Texture* Entity::GetTexture() const { return texture; }