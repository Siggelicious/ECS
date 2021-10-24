#include <Registry.h>
#include <iostream>

class Position {
public:
	float x, y;

	Position(float x, float y) {
		this->x = x;
		this->y = y;
	}
};

class RenderSystem : public System {
public:
	void Update(Registry* registry, float dt) override {
		for (auto entity : entities) {
			std::cout << registry->GetComponent<Position>(entity)->x << std::endl;
			std::cout << registry->GetComponent<Position>(entity)->y << std::endl;
		}
	}
};

void Game() {
	Registry registry;
	registry.RegisterComponent<Position>();
	registry.RegisterSystem<RenderSystem, Position>();
	Entity entity = registry.CreateEntity();
	registry.AddComponent<Position>(entity, 10.f, 20.f);

	float dt = 1;
	registry.Update<RenderSystem>(1);
}

int main() {
	Game();
}