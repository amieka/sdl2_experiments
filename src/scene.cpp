#include "scene.h"

// Texture definitions begin

void Texture::Render(int x, int y) {
  // render texture using a renderer
  SDL_Rect render_quad = {x, y, SCREEN_WIDTH, SCREEN_HEIGHT};
  SDL_Point* center = NULL;
  SDL_RendererFlip flip = SDL_FLIP_NONE;
  SDL_RenderCopyEx(current_renderer, current_texture, NULL, &render_quad, 0.00,
                   center, flip);
}

int Texture::GetWidth() const { return width; }
int Texture::GetHeight() const { return height; }

void Texture::Init(std::string texture_name) {
  std::string texture_path = "../assets/" + texture_name;
  SDL_Surface* img_surface = IMG_Load(texture_path.c_str());
  // set color key to RGBA
  SDL_SetColorKey(img_surface, SDL_TRUE,
                  SDL_MapRGB(img_surface->format, 0, 0xFF, 0xFF));
  current_texture = SDL_CreateTextureFromSurface(current_renderer, img_surface);

  if (current_texture == NULL) {
    printf("could not load texture at path = %s\n", texture_path.c_str());
  }
  width = img_surface->w;
  height = img_surface->h;
}

// Texture definitions end

// background definitions begin
void Background::Init() {
  layers.clear();
  scrolling_offset = 0;
}
void Background::AddLayer(std::string texture_path, SDL_Renderer* renderer) {
  Texture new_texture(texture_path, renderer);
  layers.push_back(new_texture);
}
void Background::Update(SDL_Event event) {
  switch (event.type) {
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
        case SDLK_LEFT:
          scrolling_direction = DIR_LEFT;
          break;
        case SDLK_RIGHT:
          scrolling_direction = DIR_RIGHT;
          break;
      }
      break;
    case SDL_KEYUP:
      switch (event.key.keysym.sym) {
        case SDLK_LEFT:
          scrolling_direction = DIR_RIGHT;
          break;
        case SDLK_RIGHT:
          scrolling_direction = DIR_LEFT;
          break;
      }
      break;
    default:
      break;
  }
}

// background definitions end

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
}

void Scene::UpdateScrollingOffsets(int x, int y) {
  // updates scrolling offsets for all the backgrounds
  scrolling_offset -= 1;
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

void Scene::RenderBackground() {
  RenderBackgroundInternal(scrolling_offset, 0);
  RenderBackgroundInternal(SCREEN_WIDTH + scrolling_offset, 0);
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

  printf("camera_x: %d, camera_y: %d\n", camera.x, camera.y);
}

void Scene::LoadEntities(SDL_Renderer* renderer) {
  // Player 1

  current_renderer = renderer;
  Entity player(PLAYER, 0, 240, 21, 33, 0, current_renderer);
  entities.push_back(player);

  // grab all the backgrounds
  const std::string backgrounds_path[4] = {
      "_11_background.png", "_10_distant_clouds.png", "_02_trees_bushes.png",
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
}

void Scene::Blit() {
  for (int idx = 0; idx < entities.size(); idx++) {
    Entity current = entities[idx];
    current.Render(camera.x, camera.y);
  }
}

// Scene definitions end