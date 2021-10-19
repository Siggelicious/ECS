#include <EntityManager.h>

Entity EntityManager::CreateEntity() {
	Entity entity;
	
	if (destroyed_entities.empty()) {
		entity = last_entity++;
	}

	else {
		entity = destroyed_entities.front();
		destroyed_entities.pop();
	}

	return entity;
}

void EntityManager::DestroyEntity(Entity entity) {
	destroyed_entities.push(entity);
}
