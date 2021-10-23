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

	signatures.insert(std::make_pair(entity, 0));

	return entity;
}

void EntityManager::DestroyEntity(Entity entity) {
	signatures.erase(entity);
	destroyed_entities.push(entity);
}
