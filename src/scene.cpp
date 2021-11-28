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

void Scene::RenderBackgroundInternal(int x, int y) {
  SDL_Rect renderQuad = {x, y, 640, 483};
  SDL_Point* center = NULL;
  SDL_RendererFlip flip = SDL_FLIP_NONE;
  SDL_RenderCopyEx(current_renderer, backgrounds[0], NULL, &renderQuad, 0.00,
                   center, flip);
  SDL_RenderCopyEx(current_renderer, backgrounds[1], NULL, &renderQuad, 0.00,
                   center, flip);
  SDL_RenderCopyEx(current_renderer, backgrounds[2], NULL, &renderQuad, 0.00,
                   center, flip);
  SDL_RenderCopyEx(current_renderer, backgrounds[3], NULL, &renderQuad, 0.00,
                   center, flip);
}

void Scene::RenderBackground() { scene_background.Render(); }

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

  printf("camera_x: %d, camera_y: %d\n", camera.x, camera.y);
}

void Scene::LoadEntities(SDL_Renderer* renderer) {
  // Player 1
  // Background new_background;
  current_renderer = renderer;
  // scene_background = new_background;
  Entity player(PLAYER, 0, 240, 21, 33, 0, current_renderer);
  entities.push_back(player);

  // grab all the backgrounds
  int num_layers = 9;
  const std::string backgrounds_names[9] = {
      "_11_background.png", "_10_distant_clouds.png", "_09_distant_clouds1.png",
      "_08_clouds.png",     "_05_hill1.png",          "_06_hill2.png",
      "_04_bushes.png",     "_02_trees_bushes.png",   "_01_ground.png"};

  const int scroll_speeds[9] = {0, 1, 2, 3, 5, 7, 9, 11, 30};

  // load an entire sprite
  Texture sprite("data.png", renderer);

  // define background rects
  const int background_tex_rects[][4] = {
      {0, 0, 640, 483},   {640, 0, 640, 483},   {1280, 0, 640, 483},
      {0, 483, 640, 483}, {640, 483, 640, 483}, {1280, 483, 640, 483},
      {0, 966, 640, 483}, {640, 966, 640, 483}, {1280, 966, 640, 483}};

  // define player rects
  for (int idx = 0; idx < num_layers; idx++) {
    scene_background.AddLayer(backgrounds_names[idx], current_renderer,
                              scroll_speeds[idx]);
  }

  // add backgrounds
  // add players
  player_idle = new Player(current_renderer, 100, 440);
  event_dispatcher->Attach(player_idle);
}

std::vector<Entity> Scene::GetEntities() const { return entities; }

void Scene::Update(SDL_Event e) {
  Entity current;
  int delta_x, delta_y, player_w, player_h;
  for (int idx = 0; idx < entities.size(); idx++) {
    current = entities[idx];
    // printf("entity type : %u\n", current.item_type);
    if (current.item_type == 0) {
      current.UpdateState(e, RUNNING);
      current.Move();
    }

    delta_x = current.GetX();
    delta_y = current.GetY();
    entities[idx].x = delta_x;
    entities[idx].y = delta_y;
    player_w = entities[idx].w;
    player_h = entities[idx].h;
  }
  // update camera
  UpdateCamera(delta_x, delta_y, player_w, player_h);
  // update scrolling offset
  UpdateScrollingOffsets(delta_x, delta_y);

  scene_background.Update(e);
}

void Scene::Blit() {
  for (int idx = 0; idx < entities.size(); idx++) {
    Entity current = entities[idx];
    current.Render(camera.x, camera.y);
  }
}

// Scene definitions end