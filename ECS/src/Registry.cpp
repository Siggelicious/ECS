#include <Registry.h>

Registry::Registry() {
	m_entity_manager = new EntityManager();
	m_component_manager = new ComponentManager();
	m_system_manager = new SystemManager();
}

Registry::Registry(uint32_t alloc_chunk_size) : Registry() {
	SetAllocationChunkSize(alloc_chunk_size);
}

Registry::~Registry() {
	delete m_entity_manager;
	delete m_component_manager;
	delete m_system_manager;
}

Entity Registry::CreateEntity() {
	return m_entity_manager->CreateEntity();
}

void Registry::DestroyEntity(Entity entity) {
	m_component_manager->EntityDestroyed(entity, m_entity_manager->GetSignature(entity));
	m_system_manager->EnityDestroyed(entity);
	m_entity_manager->DestroyEntity(entity);
}

void Registry::SetAllocationChunkSize(uint32_t alloc_chunk_size) {
	m_component_manager->SetAllocationChunkSize(alloc_chunk_size);
}