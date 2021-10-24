#pragma once
#include <cstdint>
#include <ComponentManager.h>
#include <EntityManager.h>
#include <SystemManager.h>

class Registry {
private:
	EntityManager* entity_manager;
	ComponentManager* component_manager;
	SystemManager* system_manager;

	template<typename ... Args>
	Signature CreateSystemSignature();
public:
	Registry();
	~Registry();
	Entity CreateEntity();
	void DestroyEntity(Entity entity);

	template<typename T>
	void RegisterComponent();

	template<typename T, typename ... Args>
	void AddComponent(Entity entity, Args&& ... args);

	template<typename T>
	void RemoveComponent(Entity entity);

	template<typename T>
	T* GetComponent(Entity entity);

	template<typename T, typename ... Args>
	void RegisterSystem();

	template<typename T>
	void Update();
};

template<typename ... Args>
Signature Registry::CreateSystemSignature() {
	Signature signature;
	(signature.set(component_manager->GetComponentId<Args>(), true), ...);
	return signature;
}

template<typename T>
void Registry::RegisterComponent() {
	component_manager->RegisterComponent<T>();
}

template<typename T, typename ... Args>
void Registry::AddComponent(Entity entity, Args&& ... args) {
	component_manager->AddComponent<T>(entity, std::forward<decltype(args)>(args) ...);
	entity_manager->SetSignature(entity, component_manager->GetComponentId<T>(), true);
	system_manager->EntitySignatureChanged(entity, entity_manager->GetSignature(entity));
}

template<typename T>
void Registry::RemoveComponent(Entity entity) {
	component_manager->RemoveComponent<T>(entity);
	entity_manager->SetSignature(entity, component_manager->GetComponentId<T>(), false);
	system_manager->EntitySignatureChanged(entity, entity_manager->GetSignature(entity));
}

template<typename T>
T* Registry::GetComponent(Entity entity) {
	return component_manager->GetComponent<T>(entity);
}

template<typename T, typename ... Args>
void Registry::RegisterSystem() {
	system_manager->RegisterSystem<T>(CreateSystemSignature<Args ...>());
}

template<typename T>
void Registry::Update() {
	system_manager->Update<T>();
}