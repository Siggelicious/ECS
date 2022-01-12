#pragma once
#include <cstdint>
#include <ComponentManager.h>
#include <EntityManager.h>
#include <SystemManager.h>

/*
The registry ties everything together. The only class in this library that the user should be using directly
*/

class Registry {
private:
	EntityManager* m_entity_manager; //A pointer to the entity manager.
	ComponentManager* m_component_manager; //A pointer to the component manager.
	SystemManager* m_system_manager; //A pointer to the system manager.

	template<typename ... Args>
	Signature CreateSystemSignature(); //Creates a system signature based on the template arguments, which is any number of component types.
public:
	Registry(); //Inits, creats the entity, component and system managers.
	Registry(uint32_t alloc_chunk_size); //Optional constructor for setting the allocation chunk size.
	~Registry(); //Trash cleanup.
	Entity CreateEntity(); //> EntityManager::CreateEntity.
	void DestroyEntity(Entity entity); //> EntityManager::DestroyEntity.
	void SetAllocationChunkSize(uint32_t alloc_chunk_size); //>ComponentManager::SetAllocationChunkSize.

	template<typename T>
	void RegisterComponent(); //>ComponentManager::RegisterComponent.

	template<typename T, typename ... Args>
	void AddComponent(Entity entity, Args&& ... args); //>ComponentManager::AddComponent.

	template<typename T>
	void RemoveComponent(Entity entity); //>ComponentManager::RemoveComponent.

	template<typename T>
	T* GetComponent(Entity entity); //>CompnentManager::GetComponent.

	template<typename T>
	T* GetSingleComponent(Entity entity); //>ComponentManager::GetSingelComponent.

	template<typename T, typename ... Args>
	void RegisterSystem(); //>SystemManager::RegisterSystem.

	template<typename T, typename ... Args>
	void Update(Args&& ... args); //>SystemManager::Update
};

template<typename ... Args>
Signature Registry::CreateSystemSignature() {
	Signature signature;
	(signature.set(m_component_manager->GetComponentId<Args>(), true), ...);
	return signature;
}

template<typename T>
void Registry::RegisterComponent() {
	m_component_manager->RegisterComponent<T>();
}

template<typename T, typename ... Args>
void Registry::AddComponent(Entity entity, Args&& ... args) {
	m_component_manager->AddComponent<T>(entity, std::forward<decltype(args)>(args) ...);
	m_entity_manager->SetSignature(entity, m_component_manager->GetComponentId<T>(), true);
	m_system_manager->ComponentAdded(entity, m_entity_manager->GetSignature(entity));
}

template<typename T>
void Registry::RemoveComponent(Entity entity) {
	m_component_manager->RemoveComponent<T>(entity);
	m_entity_manager->SetSignature(entity, m_component_manager->GetComponentId<T>(), false);
	m_system_manager->ComponentRemoved(entity, m_entity_manager->GetSignature(entity));
}

template<typename T>
T* Registry::GetComponent(Entity entity) {
	return m_component_manager->GetComponent<T>(entity);
}

template<typename T, typename ... Args>
void Registry::RegisterSystem() {
	m_system_manager->RegisterSystem<T>(CreateSystemSignature<Args ...>());
}

template<typename T, typename ... Args>
void Registry::Update(Args&& ... args) {
	m_system_manager->Update<T>(std::forward<decltype(args)>(args) ...);
}

template<typename T>
T* Registry::GetSingleComponent(Entity entity) {
	return m_component_manager->GetSingleComponent<T>(entity);
}