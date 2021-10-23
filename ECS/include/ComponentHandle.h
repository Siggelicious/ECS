#pragma once
#include <AComponentHandle.h>
#include <cstdint>
#include <map>
#include <Entity.h>
#include <unordered_map>

using ComponentId = uint32_t;

template<typename T>
class ComponentHandle : public AComponentHandle {
private:
	ComponentId id;
	size_t num_components;
	std::vector<T> components;
	std::unordered_map<Entity, size_t> entity_to_index;
public:
	ComponentHandle(ComponentId index);
	bool ContainsComponent(Entity entity);
	void AddComponent(Entity entity);
	void RemoveComponent(Entity entity);
	T* GetComponent(Entity entity);
	void EntityDestroyed(Entity entity);
};

template<typename T>
ComponentHandle<T>::ComponentHandle(ComponentId id) {
	this->id = id;
	num_components = 0;
}

template<typename T>
bool ComponentHandle<T>::ContainsComponent(Entity entity) {
	return entity_to_index.find(entity) != entity_to_index.end();
}


template<typename T>
void ComponentHandle<T>::AddComponent(Entity entity) {
	if (!ContainsComponent(entity)) {
		components.push_back(T());
		entity_to_index.insert(std::make_pair(entity, num_components));
	}

	num_components++;
}

template<typename T>
void ComponentHandle<T>::RemoveComponent(Entity entity) {
	if (ContainsComponent(entity)) {
		size_t index = entity_to_index[entity];

		for (auto e : entity_to_index) {
			if (e.second > index) {
				e.second--;
			}
		}

		components.erase(components.begin() + index);
		entity_to_index.erase(entity);
	}

	num_components--;
}


template<typename T>
T* ComponentHandle<T>::GetComponent(Entity entity) {
	if (ContainsComponent(entity)) {
		return &components[entity_to_index[entity]];
	}

	else 
		return nullptr;
}

template<typename T>
void ComponentHandle<T>::EntityDestroyed(Entity entity) {
	RemoveComponent(entity);
}