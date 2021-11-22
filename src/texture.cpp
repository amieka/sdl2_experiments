#include "texture.h"

void Texture::RenderWithOffset(int x, int y) {
  if (current_texture == NULL) {
    printf("current rendered texture is null\n");
  } else {
    SDL_Rect render_quad = {x, y, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Point* center = NULL;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_RenderCopyEx(current_renderer, current_texture, NULL, &render_quad,
                     0.00, center, flip);
  }
}

void Texture::Render() {
  // render texture using a renderer
  // left
  // if (scroll_direction == 0) {
  //   RenderWithOffset(scroll_offset, 0);
  //   RenderWithOffset(scroll_offset + SCREEN_WIDTH, 0);
  // }
  // // right
  // if (scroll_direction == 1) {
  //   RenderWithOffset(scroll_offset, 0);
  //   RenderWithOffset(scroll_offset + SCREEN_WIDTH, 0);
  // }

  RenderWithOffset(-scroll_offset, 0);
  RenderWithOffset(-scroll_offset + SCREEN_WIDTH, 0);
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
  SDL_FreeSurface(img_surface);
}

SDL_Texture* Texture::GetTexture() const { return current_texture; }

void Texture::UpdateScrollOffset(SDL_Event event) {
  // update scrolling offset based on the direction
  // in which the player is moving
  switch (event.type) {
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
        case SDLK_LEFT:
          scroll_direction = DIR_LEFT;
          scroll_offset += -(scroll_speed);
          break;
        case SDLK_RIGHT:
          scroll_direction = DIR_RIGHT;
          scroll_offset += (scroll_speed);
          break;
      }
      break;
    // case SDL_KEYUP:
    //   switch (event.key.keysym.sym) {
    //     case SDLK_LEFT:
    //       scroll_direction = DIR_RIGHT;
    //       scroll_offset += (scroll_speed);
    //       break;
    //     case SDLK_RIGHT:
    //       scroll_direction = DIR_LEFT;
    //       scroll_offset += -(scroll_speed);
    //       break;
    //   }
    //   break;
    default:
      break;
  }
  if (scroll_offset > SCREEN_WIDTH) {
    scroll_offset = 0;
  }

  if (scroll_offset < 0) {
    scroll_offset = 0;
  }

  Render();
}
