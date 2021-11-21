#include "scene.h"

#include <string>
void Scene::Init() {
  entities.clear();
  camera.x = 0;
  camera.y = 0;
  camera.w = SCREEN_WIDTH;
  camera.h = SCREEN_HEIGHT;
  width = SCREEN_WIDTH;
  height = SCREEN_HEIGHT;
}

void Scene::RenderBackground() {
  SDL_Rect renderQuad = {0, 0, 640, 483};
  SDL_Point* center = NULL;
  SDL_RendererFlip flip = SDL_FLIP_NONE;
  SDL_RenderCopyEx(current_renderer, current_texture, &camera, &renderQuad,
                   0.00, center, flip);

  // 3 layered backgrounds
  // render the cloud

  // render the distant cloud

  // render the trees

  // render the player
}

void Scene::UpdateCamera(int x, int y, int w, int h) {
  camera.x = (x + w / 2) - SCREEN_WIDTH / 2;
  camera.y = (y + h / 2) - SCREEN_HEIGHT / 2;

  if (camera.x < 0) {
    camera.x = 0;
  }
  if (camera.y < 0) {
    camera.y = 0;
  }

  if (camera.x > LEVEL_WIDTH - camera.w) {
    camera.x = LEVEL_WIDTH - camera.w;
  }
  if (camera.y > LEVEL_HEIGHT - camera.h) {
    camera.y = LEVEL_HEIGHT - camera.h;
  }

  printf("camera_x: %d, camera_y: %d\n", camera.x, camera.y);
}

void Scene::LoadEntities(SDL_Renderer* renderer) {
  // Player 1
  backgrounds.clear();
  current_renderer = renderer;
  Entity player(EntityType::PLAYER, 0, 240, 21, 33, 0, current_renderer);
  entities.push_back(player);

  std::string asset_path = "../assets/longer_background.png";
  current_texture = IMG_LoadTexture(current_renderer, asset_path.c_str());
  // grab all the backgrounds
  const std::string backgrounds_path[4] = {
      "_11_background.png", "_10_distant_clouds.png", "_12_trees_bushes.png",
      "_01_ground.png"};
  for (int idx = 0; idx < 4; idx++) {
    std::string background_path = "../assets/" + backgrounds_path[idx];
    SDL_Texture* bg_texture =
        IMG_LoadTexture(current_renderer, background_path.c_str());
    if (bg_texture != NULL) {
      backgrounds.push_back(bg_texture);
    }
  }
}

std::vector<Entity> Scene::GetEntities() const { return entities; }

void Scene::Update(SDL_Event e) {
  Entity current;
  for (int idx = 0; idx < entities.size(); idx++) {
    current = entities[idx];
    // printf("entity type : %u\n", current.item_type);
    if (current.item_type == 0) {
      current.UpdateState(e, CurrentState::RUNNING);
      current.Move();
    }
    entities[idx].x = current.GetX();
    entities[idx].y = current.GetY();

    UpdateCamera(current.GetX(), current.GetY(), entities[idx].w,
                 entities[idx].h);
  }
}

void Scene::Blit() {
  for (int idx = 0; idx < entities.size(); idx++) {
    Entity current = entities[idx];
    current.Render(camera.x, camera.y);
  }
}