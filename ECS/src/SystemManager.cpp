#include <SystemManager.h>

SystemManager::SystemManager() {
	last_id = 0;
}

SystemManager::~SystemManager() {
	for (const auto& pair : systems) {
		delete pair.second;
	}
}

void SystemManager::EnityDestroyed(Entity entity) {
	for (const auto& pair : systems) {
		pair.second->EntityDestroyed(entity);
	}
}

void SystemManager::EntitySignatureChanged(Entity entity, Signature entity_signature) {
	for (const auto& pair : systems) {
		pair.second->EntitySignatureChanged(entity, entity_signature);
	}
}