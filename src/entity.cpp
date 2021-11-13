#include "entity.h"

#include <string>
// std::string backgrounds[11] = {
//     "_01_ground.png",         "_02_trees_bushes.png",
//     "_03_distant_trees.png",
//     "_04_bushes.png",         "_05_hill1.png",        "_06_hill2.png",
//     "_07_huge_clouds.png",    "_08_clouds.png", "_09_distant_clouds1.png",
//     "_10_distant_clouds.png", "_11_background.png",
// };

// TODO: belongs else where
std::string backgrounds[2] = {"_02_trees_bushes.png", "_02_trees_bushes.png"};

void Entity::Move() {
	x += velx;	
}

void Entity::Render() {
	Blit();
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
  if (item_type == 0) {
    // SDL_RenderClear(current_renderer);
    printf("pos_x: %d , pos_y: %d, w: %d, h: %d\n", x, y, w, h);
  }

  //SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
  SDL_RenderCopy(current_renderer, texture, NULL, &dest);
}

void Entity::Init() {
  std::string asset_path;
  // should use a texture id to load textures
  if (item_type == EntityType::BACKGROUND) {
    asset_path = "../assets/" + backgrounds[0];
  } else {
    asset_path = "../assets/run_0.png";
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