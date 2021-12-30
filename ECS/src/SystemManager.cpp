#include <SystemManager.h>

SystemManager::SystemManager() {
	m_last_id = 0;
}

SystemManager::~SystemManager() {
	for (const auto& pair : m_systems) {
		delete pair.second;
	}
}

void SystemManager::EnityDestroyed(Entity entity, Signature entity_signature) {
	for (const auto& pair : m_systems) {
		pair.second->EntityDestroyed(entity, entity_signature);
	}
}

void SystemManager::ComponentAdded(Entity entity, Signature entity_signature) {
	for (const auto& pair : m_systems) {
		pair.second->ComponentAdded(entity, entity_signature);
	}
}

void SystemManager::ComponentRemoved(Entity entity, Signature entity_signature) {
	for (const auto& pair : m_systems) {
		pair.second->ComponentRemoved(entity, entity_signature);
	}
}