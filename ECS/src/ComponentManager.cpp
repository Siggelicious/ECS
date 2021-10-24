#include <ComponentManager.h>

ComponentManager::ComponentManager() {
	last_id = 0;
}

ComponentManager::~ComponentManager() {
	for (const auto& pair : component_handles) {
		delete pair.second;
	}
}

void ComponentManager::EntityDestroyed(Entity entity) {
	for (const auto& pair : component_handles) {
		pair.second->EntityDestroyed(entity);
	}
}
