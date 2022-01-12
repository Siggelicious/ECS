#pragma once
#include <System.h>
#include <unordered_map>

/*
This is the middleman between the registry and the systems.
Registers systems, broadcasts when a component has been added/removed or when an entity has been destroyed. 
*/

class Registry;

class SystemManager {
private:
	SystemId m_last_id; //Keeps track of the last system ID for GetSystemId().
	std::unordered_map<SystemId, System*> m_systems; //An unordered map for quick system lookups.

	template<typename T>
	T* GetSystem(); //An inline function that reinterpret_casts to the correct system type.
public:
	SystemManager(); //Inits.
	~SystemManager(); //Trash cleanup.
	void EnityDestroyed(Entity entity); //Broadcasts System::EntityDestroyed to all the systems whenever an entity has been destroyed.

	template<typename T>
	SystemId GetSystemId(); //Same as ComponentManager::GetComponetId, template magic.

	template<typename T>
	void RegisterSystem(Signature signature); //Registers a system, adds it to m_systems.

	void ComponentAdded(Entity entity, Signature entity_signature); //Broadcasts System::ComponentAdded to all systems.
	void ComponentRemoved(Entity entity, Signature entity_signature); //Broadcasts System::ComponentRemoved to all systems.

	template<typename T, typename ... Args>
	void Update(Args&& ... args); //The update function that finds the correct system with GetSystemId, call its update function and perfectly forwards the arguments.
};

template<typename T>
inline T* SystemManager::GetSystem() {
	return reinterpret_cast<T*>(m_systems[GetSystemId<T>()]);
}

template<typename T>
SystemId SystemManager::GetSystemId() {
	static SystemId system_id = m_last_id++;
	return system_id;
}

template<typename T>
void SystemManager::RegisterSystem(Signature signature) {
	T* system = new T();
	system->SetSignature(signature);
	m_systems.insert(std::make_pair(GetSystemId<T>(), system));
}

template<typename T, typename ... Args>
void SystemManager::Update(Args&& ... args) {
	GetSystem<T>()->Update(std::forward<decltype(args)>(args) ...);
}