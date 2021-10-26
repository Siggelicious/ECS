#pragma once
#include <System.h>
#include <unordered_map>

class Registry;

class SystemManager {
private:
	SystemId last_id;
	std::unordered_map<SystemId, System*> systems;

	template<typename T>
	T* GetSystem();
public:
	SystemManager();
	~SystemManager();
	void EnityDestroyed(Entity entity);

	template<typename T>
	SystemId GetSystemId();

	template<typename T>
	void RegisterSystem(Signature signature);

	void ComponentAdded(Entity entity, Signature entity_signature);
	void ComponentRemoved(Entity entity, Signature entity_signature);

	template<typename T, typename ... Args>
	void Update(Args&& ... args);
};

template<typename T>
inline T* SystemManager::GetSystem() {
	return reinterpret_cast<T*>(systems[GetSystemId<T>()]);
}

template<typename T>
SystemId SystemManager::GetSystemId() {
	static SystemId system_id = last_id++;
	return system_id;
}

template<typename T>
void SystemManager::RegisterSystem(Signature signature) {
	T* system = new T();
	system->SetSignature(signature);
	systems.insert(std::make_pair(GetSystemId<T>(), system));
}

template<typename T, typename ... Args>
void SystemManager::Update(Args&& ... args) {
	GetSystem<T>()->Update(std::forward<decltype(args)>(args) ...);
}