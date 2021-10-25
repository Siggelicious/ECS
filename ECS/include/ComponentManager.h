#pragma once
#include <vector>
#include <ComponentHandle.h>
#include <unordered_map>


class ComponentManager {
private:
	ComponentId last_id;
	std::unordered_map<ComponentId, AComponentHandle*> component_handles;
public:
	ComponentManager();
	~ComponentManager();
	void EntityDestroyed(Entity entity);

	template<typename T>
	ComponentId GetComponentId();

	template<typename T>
	ComponentHandle<T>* GetComponentHandle(ComponentId component_id);

	template<typename T>
	void RegisterComponent();

	template<typename T, typename ... Args>
	void AddComponent(Entity entity, Args&& ... args);

	template<typename T>
	void RemoveComponent(Entity entity);

	template<typename T>
	T* GetComponent(Entity entity);
};

template<typename T>
ComponentId ComponentManager::GetComponentId() {
	static ComponentId component_id = last_id++;
	return component_id;
}

template<typename T>
inline ComponentHandle<T>* ComponentManager::GetComponentHandle(ComponentId component_id) {
	return reinterpret_cast<ComponentHandle<T>*>(component_handles[component_id]);
}

template<typename T>
void ComponentManager::RegisterComponent() {
	component_handles.emplace(GetComponentId<T>(), new ComponentHandle<T>());
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