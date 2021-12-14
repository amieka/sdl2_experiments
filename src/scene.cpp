#include "scene.h"

// Scene definitions begin

void Scene::Init() {
  entities.clear();
  backgrounds.clear();
  camera.x = 0;
  camera.y = 0;
  scrolling_offset = 0;
  camera.w = SCREEN_WIDTH;
  camera.h = SCREEN_HEIGHT;
  width = SCREEN_WIDTH;
  height = SCREEN_HEIGHT;
  event_dispatcher = new EventDispatcher();
}

void Scene::UpdateScrollingOffsets(int x, int y) {
  // updates scrolling offsets for all the backgrounds
  scrolling_offset -= 10;
  if (scrolling_offset < -SCREEN_WIDTH) {
    scrolling_offset = 0;
  }
}

void Scene::RenderBackground() {
  scene_background.Render();
  player_idle->Render();
}

void Scene::RenderEntities() {}

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

  // printf("camera_x: %d, camera_y: %d\n", camera.x, camera.y);
}

void Scene::LoadEntities(SDL_Renderer* renderer) {
  // Player 1
  // Background new_background;
  // load an entire sprite
  Texture sprite("data.png", renderer);
  current_renderer = renderer;
  scene_background.SetRenderer(renderer);

  // grab all the backgrounds
  int num_layers = 9;

  const int scroll_speeds[9] = {0, 1, 2, 3, 5, 7, 9, 11, 30};

  // define background rects
  const int background_tex_rects[][4] = {
      {0, 0, 640, 483},   {640, 0, 640, 483},   {1280, 0, 640, 483},
      {0, 483, 640, 483}, {640, 483, 640, 483}, {1280, 483, 640, 483},
      {0, 966, 640, 483}, {640, 966, 640, 483}, {1280, 966, 640, 483}};

  scene_background.SetTexture(sprite.GetTexture());
  for (int idx = 0; idx < num_layers; idx++) {
    Layer new_layer;
    new_layer.scroll_speed = scroll_speeds[num_layers - idx - 1];
    new_layer.scrolling_offset = 0;
    SDL_Rect r;
    r.x = background_tex_rects[idx][0];
    r.y = background_tex_rects[idx][1];
    r.w = background_tex_rects[idx][2];
    r.h = background_tex_rects[idx][3];
    new_layer.rect = r;
    scene_background.AddLayer(new_layer);
  }

  // add backgrounds
  // add players
  player_idle = new Player(current_renderer, 100, 350);
  player_idle->SetTexture(sprite.GetTexture());
  event_dispatcher->Attach(player_idle);
}

std::vector<Entity> Scene::GetEntities() const { return entities; }

// Not used
void Scene::Update(SDL_Event e) {
  player_idle->Update(e);
  player_idle->Move();
  // update camera
  UpdateCamera(player_idle->GetX(), player_idle->GetY(),
               player_idle->GetWidth(), player_idle->GetHeight());

  scene_background.Update(e);
  player_idle->Render();
}

// Scene definitions end