#include <iostream>
#include <ComponentManager.h>
#include <ComponentHandle.h>
#include <AComponentHandle.h>
#include <EntityManager.h>
#include <Registry.h>
#include <System.h>

struct Position {
	float x, y;
	Position(float x, float y) {
		this->x = x;
		this->y = y;
	}
};

class RenderSystem : public System {
public:
	void Update() override {
		for (auto entity : entities) {
			
		}
		std::cout << entities.size() << std::endl;
	}
};


void TestEverything() {
	Registry registry;
	registry.RegisterComponent<Position>();
	registry.RegisterSystem<RenderSystem, Position>();

	Entity entity = registry.CreateEntity();

	registry.AddComponent<Position>(entity, 10.f, 20.f);
	
	for (int i = 0; i < 1000; i++) {
		registry.Update<RenderSystem>();
	}

	registry.DestroyEntity(entity);

	for (int i = 0; i < 1000; i++) {
		registry.Update<RenderSystem>();
	}
}

int main() {
	TestEverything();

	return 0;
}