#pragma once
#include <AComponentHandle.h>
#include <cstdint>
#include <map>
#include <unordered_map>

template<typename T>
class ComponentHandle : public AComponentHandle {
private:
	std::pair<Entity, T>* m_components;
	size_t m_capacity;
	size_t m_size;

	std::pair<Entity, T>* End();
	std::pair<Entity, T>* LowerBound(Entity entity);
public:
	ComponentHandle(uint32_t alloc_chunk_size);
	~ComponentHandle();
	template<typename ... Args>
	void AddComponent(Entity entity, Args&& ... args);
	void RemoveComponent(Entity entity);
	T* GetComponent(Entity entity);
	T* GetSingleComponent(Entity entity);
	void EntityDestroyed(Entity entity) override;
};

template<typename T>
inline std::pair<Entity, T>* ComponentHandle<T>::End() {
	return m_components + (m_size - 1);
}

template<typename T>
inline std::pair<Entity, T>* ComponentHandle<T>::LowerBound(Entity entity) {
	std::pair<Entity, T>* end = End();
	
	if (end == nullptr)
		return m_components;

	std::pair<Entity, T>* pos = std::lower_bound(m_components, end, entity, [](const auto& a, const auto& b) {
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

		if (pos < End() + 1) {
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

	if (pos < End()) {
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