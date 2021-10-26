#pragma once
#include <AComponentHandle.h>
#include <cstdint>
#include <map>
#include <unordered_map>

template<typename T>
class ComponentHandle : public AComponentHandle {
private:
	std::vector<std::pair<Entity, T>> components;
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

}

template<typename T>
ComponentHandle<T>::~ComponentHandle() {

}

template<typename T>
template<typename ... Args>
void ComponentHandle<T>::AddComponent(Entity entity, Args&& ... args) {
	auto it = std::lower_bound(components.begin(), components.end(), entity, [](const auto& a, const auto& b) {
		return (a.first < b);
	});

	components.emplace(it, entity, T(std::forward<decltype(args)>(args) ...));
}

template<typename T>
void ComponentHandle<T>::RemoveComponent(Entity entity) {
	auto it = std::lower_bound(components.begin(), components.end(), entity, [](const auto& a, const auto& b) {
		return (a.first < b);
	});

	components.erase(it);
}


template<typename T>
T* ComponentHandle<T>::GetComponent(Entity entity) {
	static size_t last_index = 0;

	if (last_index >= components.size() || entity < components[last_index].first)
		last_index = 0;

	for (size_t i = last_index; i < components.size(); i++) {
		if (entity == components[i].first) {
			last_index = i + 1;

			return &components[i].second;
		}
	}

	return nullptr;
}

template<typename T>
void ComponentHandle<T>::EntityDestroyed(Entity entity) {
	RemoveComponent(entity);
}