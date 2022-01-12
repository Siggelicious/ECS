#pragma once
#include <AComponentHandle.h>
#include <cstdint>
#include <map>
#include <unordered_map>

/*
Inherits from AComponentHandle and is basically the middleman between component and component manager.
*/

template<typename T> //Typename T is the component type, PhysicsComponent for exampel.
class ComponentHandle : public AComponentHandle {
private:
	std::pair<Entity, T>* m_components; //A pointer to the first element in the component array. Basically a continuous sorted array where all of our components of type T are stored.
	size_t m_capacity; //Just the capacity of the array, equivalent of std::vector::capacity().
	size_t m_size; //The size of the array, basically just the living amount of components of type T.

	std::pair<Entity, T>* Back(); //An inline function for retrieving the address of the last component in the array, useful for a lot of std::algorithms. 
	std::pair<Entity, T>* LowerBound(Entity entity); //An inline function for finding the sorted position for an entity-component pair in the component array.
public:
	ComponentHandle(uint32_t alloc_chunk_size); //Sets the m_allocation_chunk_size and allocates for the component array.
	~ComponentHandle(); //Destroys all living components to prevent memory leaks.

	template<typename ... Args>
	void AddComponent(Entity entity, Args&& ... args); /*
													   Adds a component to the component array, with fold expressions and perfect forwarding we're able to pass the constructor arguments for any component type.
													   This does unfortunately mean we have to have a default constructor for each component type, I am not sure if that causes any performance loss but I'd be surprised if it did.
													   */

	void RemoveComponent(Entity entity); //Self explanatory, removes and frees the component from memory, keeps the array packed and sorted.
	T* GetComponent(Entity entity); //Gets a component and by using a static variable we're able to have O(n) iteration times where n is m_size.
	T* GetSingleComponent(Entity entity); //Gets a single component. Should never be used when iterating, but has the lookup time complexity of O(log n).
	void EntityDestroyed(Entity entity) override;
};

template<typename T>
inline std::pair<Entity, T>* ComponentHandle<T>::Back() {
	return m_components + (m_size - 1);
}

template<typename T>
inline std::pair<Entity, T>* ComponentHandle<T>::LowerBound(Entity entity) {
	std::pair<Entity, T>* back = Back();

	if (back == nullptr)
		return m_components;

	std::pair<Entity, T>* pos = std::lower_bound(m_components, back, entity, [](const auto& a, const auto& b) {
		return (a.first < b);
		});

	return pos;
}

template<typename T>
ComponentHandle<T>::ComponentHandle(uint32_t alloc_chunk_size) {
	m_alloc_chunk_size = alloc_chunk_size;
	m_components = new std::pair<Entity, T>[m_alloc_chunk_size];
	m_capacity = m_alloc_chunk_size;
	m_size = 0;
}

template<typename T>
ComponentHandle<T>::~ComponentHandle() {
	delete[] m_components;
}

template<typename T>
template<typename ... Args>
void ComponentHandle<T>::AddComponent(Entity entity, Args&& ... args) {
	//old code, ignore

	/*
	auto it = std::lower_bound(m_components.begin(), m_components.end(), entity, [](const auto& a, const auto& b) {
		return (a.first < b);
	});


	m_components.emplace(it, entity, T(std::forward<decltype(args)>(args) ...));
	*/

	if (m_capacity <= m_size + 1) {
		m_capacity += m_alloc_chunk_size;
		std::pair<Entity, T>* components = new std::pair<Entity, T>[m_capacity];
		memcpy(components, m_components, m_size * sizeof(std::pair<Entity, T>));
		delete[] m_components;
		m_components = components;
	}

	std::pair<Entity, T>* pos;

	if (m_size == 0) {
		pos = m_components;
	}

	else {
		pos = LowerBound(entity);

		if (pos < Back() + 1) {
			memcpy(pos + 1, pos, (m_components - pos + m_size) * sizeof(std::pair<Entity, T>));
		}
	}

	*pos = std::make_pair(entity, T(std::forward<decltype(args)>(args) ...));

	m_size++;
}

template<typename T>
void ComponentHandle<T>::RemoveComponent(Entity entity) {
	//old code, ignore

	/*
	auto it = std::lower_bound(m_components.begin(), m_components.end(), entity, [](const auto& a, const auto& b) {
		return (a.first < b);
	});

	m_components.erase(it);
	*/

	std::pair<Entity, T>* pos = LowerBound(entity);

	if (pos < Back()) {
		memcpy(pos, pos + 1, (m_components - pos + m_size) * sizeof(std::pair<Entity, T>));
	}

	m_size--;
}

template<typename T>
T* ComponentHandle<T>::GetComponent(Entity entity) {
	//old code, ignore

	/*
	static size_t last_index = 0;

	if (last_index >= m_components.size() || entity < m_components[last_index].first)
		last_index = 0;

	for (size_t i = last_index; i < m_components.size(); i++) {
		if (entity == m_components[i].first) {
			last_index = i + 1;

			return &m_components[i].second;
		}
	}

	return nullptr;
	*/

	static size_t last_index = 0;

	if (last_index >= m_size || entity < m_components[last_index].first)
		last_index = 0;

	for (size_t i = last_index; i < m_size; i++) {
		if (entity == m_components[i].first) {
			last_index = i + 1;

			return &m_components[i].second;
		}
	}

	return nullptr;
}

template<typename T>
T* ComponentHandle<T>::GetSingleComponent(Entity entity) {
	//old code, ignore

	/*
	auto it = std::lower_bound(m_components.begin(), m_components.end(), entity, [](const auto& a, const auto& b) {
		return (a.first < b);
	});

	return &it->second;
	*/

	return &LowerBound(entity)->second;
}


template<typename T>
void ComponentHandle<T>::EntityDestroyed(Entity entity) {
	RemoveComponent(entity);
}