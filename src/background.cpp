#include "background.h"

void Background::Init() {
  layers.clear();
  scrolling_offset = 0;
}

void Background::UpdateScrollOffset() {
  // do nothing yet
  // ideally background should listen for an event change from the player
  // and update the background offset accordingly
}

void Background::SetTexture(SDL_Texture* texture) { current_texture = texture; }

void Background::AddLayer(std::string texture_path, SDL_Renderer* renderer,
                          int scroll_speed) {
  Texture new_texture(texture_path, renderer, scroll_speed);
  layers.push_back(new_texture);
}

void Background::AddLayer(SDL_Rect rect, SDL_Renderer* renderer,
                          int scroll_speed) {}

void Background::Update(SDL_Event event) {
  for (int i = 0; i < layers.size(); i++) {
    Texture tmp_texture = layers[i];
    tmp_texture.UpdateScrollOffset(event);
    layers[i] = tmp_texture;
  }
}

void Background::Render() {
  // iterate through all the layers and render one by one
  for (int i = 0; i < layers.size(); i++) {
    Texture tmp_texture = layers[i];
    tmp_texture.Render();
  }
}

void Background::Render(int x, int y, bool* scroll_dir) {
  for (int i = 0; i < layers.size(); i++) {
    Texture texture = layers[i];

    if (scroll_dir[0] == 1) {
      // moving left
      texture.RenderWithOffset(x, 0);
      texture.RenderWithOffset(x - SCREEN_WIDTH, 0);
    }

    if (scroll_dir[1] == 1) {
      // moving right
      texture.RenderWithOffset(-1 * x, 0);
      texture.RenderWithOffset(-1 * x + SCREEN_WIDTH, 0);
    }
  }
}