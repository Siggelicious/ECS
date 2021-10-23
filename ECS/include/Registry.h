#pragma once
#include <cstdint>
#include <Entity.h>
#include <ComponentManager.h>
#include <EntityManager.h>

class Registry {
private:
	EntityManager* entity_manager;
	ComponentManager* component_manager;
public:
	Registry();
	~Registry();
	Entity CreateEntity();
	void DestroyEntity(Entity entity);

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
void Registry::RegisterComponent() {
	component_manager->RegisterComponent<T>();
}

template<typename T>
void Registry::AddComponent(Entity entity) {
	component_manager->AddComponent<T>(entity);
}

template<typename T>
void Registry::RemoveComponent(Entity entity) {
	component_manager->RemoveComponent<T>(entity);
}

template<typename T>
T* Registry::GetComponent(Entity entity) {
	return component_manager->GetComponent<T>(entity);
}