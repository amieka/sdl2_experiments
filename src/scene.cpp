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
  std::string asset_path = "../assets/_02_trees_bushes.png";
  SDL_Texture* texture = IMG_LoadTexture(current_renderer, asset_path.c_str());
  SDL_RenderCopy(current_renderer, texture, NULL, &camera);
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

  Entity player(EntityType::PLAYER, 0, 0, 21, 33, 0, renderer);
  // Background
  entities.push_back(player);
  // entities.push_back(background);

  current_renderer = renderer;
}

std::vector<Entity> Scene::GetEntities() const { return entities; }

void Scene::Update(SDL_Event e) {
  int a = 0;
  for (int idx = 0; idx < entities.size(); idx++) {
    Entity current = entities[idx];
    // printf("entity type : %u\n", current.item_type);
    if (current.item_type == 0) {
      current.UpdateState(e, CurrentState::RUNNING);
      current.Move();
    }
    entities[idx].x = current.GetX();
    entities[idx].y = current.GetY();

    UpdateCamera(current.GetX(), current.GetY(), entities[idx].w,
                 entities[idx].h);
    current.Render(camera.x, camera.y);
  }
  RenderBackground();
}

void Scene::Blit() {
  for (int idx = 0; idx < entities.size(); idx++) {
    Entity current = entities[idx];
    current.Render(camera.x, camera.y);
  }
  RenderBackground();
}