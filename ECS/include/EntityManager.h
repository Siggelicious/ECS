#pragma once
#include <Entity.h>
#include <queue>

class EntityManager {
private:
	Entity last_entity = 0;
	std::queue<Entity> destroyed_entities;
public:
	Entity CreateEntity();
	void DestroyEntity(Entity entity);
};