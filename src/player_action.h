#ifndef PLAYER_ACTION
#define PLAYER_ACTION

class Player;
class PlayerAction {
 public:
  PlayerAction() {}
  ~PlayerAction() {}
  void Start();
  void Update(Player& player);
};

#endif