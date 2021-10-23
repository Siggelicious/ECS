#include <iostream>
#include <ComponentManager.h>
#include <ComponentHandle.h>
#include <AComponentHandle.h>
#include <EntityManager.h>
#include <Registry.h>

struct Position {
	float x, y;
};


void TestEverything() {
	Registry registry;

	registry.RegisterComponent<Position>();
	Entity entity = registry.CreateEntity();
	registry.AddComponent<Position>(entity);
	registry.GetComponent<Position>(entity);
	registry.RemoveComponent<Position>(entity);
	registry.GetComponent<Position>(entity);
}

int main() {


	TestEverything();

	return 0;
}