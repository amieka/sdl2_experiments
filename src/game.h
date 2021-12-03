struct Game {
  SDL_Window* window;
  SDL_Renderer* renderer;
  Scene current_scene;
  SDL_Texture* texture;
  int x, y;
  std::vector<SDL_Texture*> player_textures;
  Player* player_idle;
  Player* player_walking;
  void Init();
  void PrepareScene();
  void PresentScene();
  void HandleInput();
  void UpdateBackground();
  void CreateScene();
  void UpdateScene(SDL_Event e);
  void LoadTexture();
  void AnimatePlayer();
  Game(Scene scene) {
    current_scene = scene;
    Init();
  }
};