#pragma once
#include <Entity.h>
#include <queue>
#include <map>

class EntityManager {
private:
	Entity last_entity = 0;
	std::queue<Entity> destroyed_entities;
	std::map<Entity, Signature> signatures;
public:
	Entity CreateEntity();
	void DestroyEntity(Entity entity);
};