#include <ComponentManager.h>

ComponentManager::ComponentManager() {
	m_last_id = 0;
	m_alloc_chunk_size = 128;
}

ComponentManager::~ComponentManager() {
	for (const auto& pair : m_component_handles) {
		delete pair.second;
	}
}

void ComponentManager::EntityDestroyed(Entity entity, Signature entity_signature) {
	for (const auto& pair : m_component_handles) {
		if (entity_signature.test(pair.first)) {
			pair.second->EntityDestroyed(entity);
		}
	}
}

void ComponentManager::SetAllocationChunkSize(uint32_t alloc_chunk_size) {
	m_alloc_chunk_size = alloc_chunk_size;

	for (const auto& pair : m_component_handles) {
		pair.second->SetAllocationChunkSize(m_alloc_chunk_size);
	}
}