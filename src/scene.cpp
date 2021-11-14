#include "scene.h"

void Scene::Init() { entities.clear(); }

void Scene::LoadEntities(SDL_Renderer* renderer) {
  // Player 1
  Entity player(EntityType::PLAYER, 310, 270, 21, 33, 0, renderer);
  // Background
  Entity background(EntityType::BACKGROUND, 0, 0, 640, 483, 1, renderer);
  entities.push_back(player);
  //entities.push_back(background);
}

std::vector<Entity> Scene::GetEntities() const { return entities; }

void Scene::Update(SDL_Event e) {
	int a = 0;
	for(int idx = 0; idx < entities.size(); idx++) {
		Entity current = entities[idx];
		//printf("entity type : %u\n", current.item_type);
		if (current.item_type == 0) {
			current.UpdateState(e,CurrentState::RUNNING);
			current.Move();
		}
		entities[idx].x = current.GetX();
		entities[idx].y = current.GetY();
		current.Render();
	}
}

void Scene::Blit() {
	for(int idx = 0; idx < entities.size(); idx++) {
		Entity current = entities[idx];
		current.Render();
	}
}