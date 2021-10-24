#pragma once
#include <AComponentHandle.h>
#include <cstdint>
#include <map>
#include <unordered_map>

template<typename T>
class ComponentHandle : public AComponentHandle {
private:
	size_t num_components;
	std::vector<T> components;
	std::unordered_map<Entity, size_t> entity_to_index;
public:
	ComponentHandle();
	~ComponentHandle();
	template<typename ... Args>
	void AddComponent(Entity entity, Args&& ... args);
	void RemoveComponent(Entity entity);
	T* GetComponent(Entity entity);
	void EntityDestroyed(Entity entity) override;
};

template<typename T>
ComponentHandle<T>::ComponentHandle() {
	num_components = 0;
}

template<typename T>
ComponentHandle<T>::~ComponentHandle() {

}

template<typename T>
template<typename ... Args>
void ComponentHandle<T>::AddComponent(Entity entity, Args&& ... args) {
	components.emplace_back(std::forward<decltype(args)>(args) ...);
	entity_to_index.insert(std::make_pair(entity, num_components));
	num_components++;
}

template<typename T>
void ComponentHandle<T>::RemoveComponent(Entity entity) {
	size_t index = entity_to_index[entity];

	for (auto& pair : entity_to_index) {
		if (pair.second > index) {
			pair.second--;
		}
	}

	components.erase(components.begin() + index);
	entity_to_index.erase(entity);
	num_components--;
}


template<typename T>
T* ComponentHandle<T>::GetComponent(Entity entity) {
	return &components[entity_to_index[entity]];
}

template<typename T>
void ComponentHandle<T>::EntityDestroyed(Entity entity) {
	RemoveComponent(entity);
}