#pragma once
#include <Entity.h>
#include <vector>
#include <ComponentHandle.h>
#include <unordered_map>
#include <iostream>

class ComponentManager {
private:
	ComponentId last_id;
	std::unordered_map<ComponentId, AComponentHandle*> component_handles;
	
	template<typename T>
	ComponentId GetComponentId();

	template<typename T>
	ComponentHandle<T>* GetComponentHandle(ComponentId component_id);

	bool IsRegistered(ComponentId component_id);
public:
	ComponentManager();
	virtual ~ComponentManager();
	void EntityDestroyed(Entity entity);

	template<typename T>
	void RegisterComponent();

	template<typename T>
	void AddComponent(Entity entity);

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
ComponentHandle<T>* ComponentManager::GetComponentHandle(ComponentId component_id) {
	return reinterpret_cast<ComponentHandle<T>*>(component_handles[component_id]);
}

template<typename T>
void ComponentManager::RegisterComponent() {
	ComponentId component_id = GetComponentId<T>();

	if (!IsRegistered(component_id)) {
		ComponentHandle<T>* component_handle = new ComponentHandle<T>(component_id);
		component_handles.insert(std::make_pair(component_id, component_handle));
	}
}

template<typename T>
void ComponentManager::AddComponent(Entity entity) {
	ComponentId component_id = GetComponentId<T>();

	if (IsRegistered(component_id)) {
		ComponentHandle<T>* component_handle = GetComponentHandle<T>(component_id);
		component_handle->AddComponent(entity);
	}
}

template<typename T>
void ComponentManager::RemoveComponent(Entity entity) {
	ComponentId component_id = GetComponentId<T>();

	if (IsRegistered(component_id)) {
		ComponentHandle<T>* component_handle = GetComponentHandle<T>(component_id);
		component_handle->RemoveComponent(entity);
	}
}

template<typename T>
T* ComponentManager::GetComponent(Entity entity) {
	ComponentId component_id = GetComponentId<T>();

	if (IsRegistered(component_id)) {
		ComponentHandle<T>* component_handle = GetComponentHandle<T>(component_id);
		return component_handle->GetComponent(entity);
	}

	return nullptr;
}