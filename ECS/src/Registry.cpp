#include <Registry.h>

Registry::Registry() {
	entity_manager = new EntityManager();
	component_manager = new ComponentManager();
}

Registry::~Registry() {
	delete entity_manager;
	delete component_manager;
}


Entity Registry::CreateEntity() {
	return entity_manager->CreateEntity();
}

void Registry::DestroyEntity(Entity entity) {
	entity_manager->DestroyEntity(entity);
	component_manager->EntityDestroyed(entity);
}