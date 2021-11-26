#include "player.h"

void Player::Init() {
  // fill out the layers
  for (int i = 0; i < 2; i++) {
    // int* action[4] = StateLayers[i];
  }
}

void Player::Render() {
  // do nothing yet
  if (this->root_texture != NULL) {
    printf("player texture can be rendered");
  }
}

void Player::Render(int x, int y) {
  // render at a certain x,y pos
}
void Player::Move(SDL_Event e) {
  // do nothing yet
  player_state = WALKING;
}

void Player::SetState(PlayerState state) { player_state = state; }

int Player::GetX() const { return 1; }

int Player::GetY() const { return 2; }