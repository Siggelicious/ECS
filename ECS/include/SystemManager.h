#pragma once
#include <System.h>
#include <unordered_map>

class SystemManager {
private:
	SystemId last_id;
	std::unordered_map<SystemId, System*> systems;
public:
	SystemManager();
	~SystemManager();
	void EnityDestroyed(Entity entity);

	template<typename T>
	SystemId GetSystemId();

	template<typename T>
	void RegisterSystem(Signature signature);

	void EntitySignatureChanged(Entity entity, Signature entity_signature);

	template<typename T>
	void Update();
};

template<typename T>
SystemId SystemManager::GetSystemId() {
	static SystemId system_id = last_id++;
	return system_id;
}

template<typename T>
void SystemManager::RegisterSystem(Signature signature) {
	System* system = new T();
	systems.insert(std::make_pair(GetSystemId<T>(), system));
	system->SetSignature(signature);
}

template<typename T>
void SystemManager::Update() {
	systems[GetSystemId<T>()]->Update();
}