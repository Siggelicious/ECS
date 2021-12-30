#pragma once
#include <vector>
#include <ComponentHandle.h>
#include <unordered_map>


class ComponentManager {
private:
	ComponentId m_last_id;
	std::unordered_map<ComponentId, AComponentHandle*> m_component_handles;
	uint32_t m_alloc_chunk_size;

	template<typename T>
	ComponentHandle<T>* GetComponentHandle(ComponentId component_id);
public:
	ComponentManager();
	~ComponentManager();
	void EntityDestroyed(Entity entity, Signature entity_signature);
	void SetAllocationChunkSize(uint32_t alloc_chunk_size);

	template<typename T>
	ComponentId GetComponentId();

	template<typename T>
	void RegisterComponent();

	template<typename T, typename ... Args>
	void AddComponent(Entity entity, Args&& ... args);

	template<typename T>
	void RemoveComponent(Entity entity);

	template<typename T>
	T* GetComponent(Entity entity);

	template<typename T>
	T* GetSingleComponent(Entity entity);
};

template<typename T>
ComponentId ComponentManager::GetComponentId() {
	static ComponentId component_id = m_last_id++;
	return component_id;
}

template<typename T>
inline ComponentHandle<T>* ComponentManager::GetComponentHandle(ComponentId component_id) {
	return reinterpret_cast<ComponentHandle<T>*>(m_component_handles[component_id]);
}

template<typename T>
void ComponentManager::RegisterComponent() {
	ComponentHandle<T>* component_handle = new ComponentHandle<T>(m_alloc_chunk_size);
	component_handle->SetAllocationChunkSize(m_alloc_chunk_size);
	m_component_handles.insert(std::make_pair(GetComponentId<T>(), component_handle));
	//m_component_handles.emplace(GetComponentId<T>(), new ComponentHandle<T>());
}

template<typename T, typename ... Args>
void ComponentManager::AddComponent(Entity entity, Args&& ... args) {
	ComponentId component_id = GetComponentId<T>();
	ComponentHandle<T>* component_handle = GetComponentHandle<T>(component_id);
	component_handle->AddComponent(entity, std::forward<decltype(args)>(args) ...);
}

template<typename T>
void ComponentManager::RemoveComponent(Entity entity) {
	ComponentId component_id = GetComponentId<T>();
	ComponentHandle<T>* component_handle = GetComponentHandle<T>(component_id);
	component_handle->RemoveComponent(entity);
}

template<typename T>
T* ComponentManager::GetComponent(Entity entity) {
	ComponentId component_id = GetComponentId<T>();
	ComponentHandle<T>* component_handle = GetComponentHandle<T>(component_id);
	return component_handle->GetComponent(entity);
}

template<typename T>
T* ComponentManager::GetSingleComponent(Entity entity) {
	ComponentId component_id = GetComponentId<T>();
	ComponentHandle<T>* component_handle = GetComponentHandle<T>(component_id);
	return component_handle->GetSingleComponent(entity);
}