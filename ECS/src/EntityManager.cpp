#include <EntityManager.h>

EntityManager::EntityManager() {
	last_entity = 0;
}

Entity EntityManager::CreateEntity() {
	Entity entity;
	
	if (destroyed_entities.empty()) {
		entity = last_entity++;
	}

	else {
		entity = destroyed_entities.front();
		destroyed_entities.pop();
	}

	signatures.emplace(entity, Signature());

	return entity;
}

void EntityManager::DestroyEntity(Entity entity) {
	signatures.erase(entity);
	destroyed_entities.push(entity);
}

void EntityManager::SetSignature(Entity entity, ComponentId component_id, bool value) {
	signatures[entity].set(component_id, value);
}

Signature EntityManager::GetSignature(Entity entity) {
	return signatures[entity];
}