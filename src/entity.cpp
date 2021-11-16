#include "entity.h"

#include <string>

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
      current_state = CurrentState::STILL;
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

  SDL_Rect dest;

  dest.x = x;
  dest.y = y;
  dest.w = w;
  dest.h = h;

  SDL_RenderCopy(current_renderer, texture, NULL, &dest);
  // SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
}

void Entity::Init() {
  std::string asset_path;
  frames.clear();
  // should use a texture id to load textures
  if (item_type == 1) {
    asset_path = "../assets/" + backgrounds[0];
  } else {
    asset_path = "../assets/run_0.png";
    // load all the frames here
    for (int idx = 0; idx < 8; idx++) {
      SDL_Rect frame;
      frame.x = 0;
      frame.y = 0;
      std::string frame_path = "../assets/run_" + std::to_string(idx) + ".png";
      SDL_Texture* texture_frame =
          IMG_LoadTexture(current_renderer, frame_path.c_str());
      SDL_QueryTexture(texture_frame, NULL, NULL, &frame.w, &frame.h);
      printf("%d %d\n", frame.w, frame.h);
      frames.push_back(frame);
      tex_frames.push_back(texture_frame);
      SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                     "Loading %s", frame_path.c_str());
      free(texture_frame);
    }
  }
  SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                 "Loading %s", asset_path.c_str());
  texture = IMG_LoadTexture(current_renderer, asset_path.c_str());
  if (texture == NULL) {
    printf("texture not loaded\n");
  }

  Blit();
}

int Entity::GetX() const { return x; }

int Entity::GetY() const { return y; }

SDL_Texture* Entity::GetTexture() const { return texture; }