#include "background.h"

void Background::Init() {
  layers.clear();
  layer_rects.clear();
  scrolling_offset = 0;
}

void Background::SetRenderer(SDL_Renderer* r) { current_renderer = r; }

void Background::UpdateScrollOffset(SDL_Event event, Layer& current_layer) {
  switch (event.type) {
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
        case SDLK_LEFT:
          scrolling_direction = DIR_LEFT;
          current_layer.scrolling_offset += (current_layer.scroll_speed);
          break;
        case SDLK_RIGHT:
          scrolling_direction = DIR_RIGHT;
          current_layer.scrolling_offset -= (current_layer.scroll_speed);
          break;
      }
      break;
    default:
      break;
  }

  // handle right scroll
  if (scrolling_direction == 1) {
    if (current_layer.scrolling_offset < -SCREEN_WIDTH) {
      current_layer.scrolling_offset = 0;
    }
  }

  // handle left scroll
  if (scrolling_direction == 0) {
    if (current_layer.scrolling_offset > SCREEN_WIDTH) {
      current_layer.scrolling_offset = 0;
    }
  }
}

void Background::SetTexture(SDL_Texture* texture) { current_texture = texture; }

void Background::AddLayer(std::string texture_path, SDL_Renderer* renderer,
                          int scroll_speed) {
  Texture new_texture(texture_path, renderer, scroll_speed);
  layers.push_back(new_texture);
}

void Background::AddLayer(Layer new_layer) { layer_rects.push_back(new_layer); }

void Background::Update(SDL_Event event) {
  for (int i = 0; i < layer_rects.size(); i++) {
    Layer tmp_layer = layer_rects[i];
    UpdateScrollOffset(event, tmp_layer);

    if (scrolling_direction == 0) {
      RenderLayer(tmp_layer, tmp_layer.scrolling_offset, 0);
      RenderLayer(tmp_layer, tmp_layer.scrolling_offset - SCREEN_WIDTH, 0);
    }
    if (scrolling_direction == 1) {
      RenderLayer(tmp_layer, tmp_layer.scrolling_offset, 0);
      RenderLayer(tmp_layer, tmp_layer.scrolling_offset - SCREEN_WIDTH, 0);
    }

    // printf("scrolling offset :: %d \n", tmp_layer.scrolling_offset);
  }
}

void Background::Render() {
  // iterate through all the layers and render one by one
  // render from the last to first
  int s = layer_rects.size();
  for (int i = 0; i < layer_rects.size(); i++) {
    Layer tmp_layer = layer_rects[s - i - 1];
    RenderLayer(tmp_layer, 0, 0);
  }
}

void Background::RenderLayer(Layer current_layer, int x, int y) {
  SDL_Rect render_quad = {x, y, SCREEN_WIDTH, SCREEN_HEIGHT};

  SDL_Point* center = NULL;

  SDL_RendererFlip flip = SDL_FLIP_NONE;
  SDL_RenderCopyEx(current_renderer, current_texture, &current_layer.rect,
                   &render_quad, 0.00, center, flip);
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