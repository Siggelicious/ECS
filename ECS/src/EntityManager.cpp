#include <EntityManager.h>

EntityManager::EntityManager() {
	m_last_entity = 0;
}

Entity EntityManager::CreateEntity() {
	Entity entity;
	
	if (m_destroyed_entities.empty()) {
		entity = m_last_entity++;
	}

	else {
		entity = m_destroyed_entities.front();
		m_destroyed_entities.pop();
	}

	m_signatures.emplace(entity, Signature());

	return entity;
}

void EntityManager::DestroyEntity(Entity entity) {
	m_signatures.erase(entity);
	m_destroyed_entities.push(entity);
}

void EntityManager::SetSignature(Entity entity, ComponentId component_id, bool value) {
	m_signatures[entity].set(component_id, value);
}

Signature EntityManager::GetSignature(Entity entity) {
	return m_signatures[entity];
}