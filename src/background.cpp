#include "background.h"

void Background::Init() {
  layers.clear();
  scrolling_offset = 0;
}

void Background::AddLayer(std::string texture_path, SDL_Renderer* renderer,
                          int scroll_speed) {
  Texture new_texture(texture_path, renderer, scroll_speed);
  layers.push_back(new_texture);
}

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