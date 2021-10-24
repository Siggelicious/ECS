#pragma once
#include <queue>
#include <unordered_map>
#include <Types.h>

class EntityManager {
private:
	Entity last_entity;
	std::queue<Entity> destroyed_entities;
	std::unordered_map<Entity, Signature> signatures;
public:
	EntityManager();
	Entity CreateEntity();
	void DestroyEntity(Entity entity);
	void SetSignature(Entity entity, ComponentId component_id, bool value);
	Signature GetSignature(Entity entity);
};