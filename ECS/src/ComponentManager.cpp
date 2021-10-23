#include <ComponentManager.h>

bool ComponentManager::IsRegistered(ComponentId component_id) {
	return component_handles.find(component_id) != component_handles.end();
}

ComponentManager::ComponentManager() {
	last_id = 0;
}

ComponentManager::~ComponentManager() {
	
	for (auto component_handle : component_handles) {
		delete component_handle.second;
	}
}

void ComponentManager::EntityDestroyed(Entity entity) {
	for (auto e : component_handles) {
		e.second->EntityDestroyed(entity);
	}
}
