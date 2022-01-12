#pragma once
#include <vector>
#include <ComponentHandle.h>
#include <unordered_map>

/*
This is the middleman between the registry and the component handle. 
This is where we create component handles, broadcast to the component handles that an entity has been destroyed and clean up the trash.
*/

class ComponentManager {
private:
	ComponentId m_last_id; //To keep track of the latest component ID for GetComponentId().
	std::unordered_map<ComponentId, AComponentHandle*> m_component_handles; //An unordered map that stores pointers to all of our component handles and their ids.
	uint32_t m_alloc_chunk_size; //Basically the "default" m_alloc_chunk_size, this gets passed onto the ComponentHandles when they are created.

	template<typename T>
	ComponentHandle<T>* GetComponentHandle(ComponentId component_id); //Just retrieves a component handle of type T, unfortunately we have to reinterpret_cast but afaik it's completely safe in this case.
public:
	ComponentManager(); //Just inits the member variables.
	~ComponentManager(); //Trash cleanup, destroys all the component handles.
	void EntityDestroyed(Entity entity, Signature entity_signature); //Broadcasts to all the component handles that an entity has been destroyed.
	void SetAllocationChunkSize(uint32_t alloc_chunk_size); //Sets the allocation chunk size and broadcasts it to the component handles (will likely get changed).

	template<typename T>
	ComponentId GetComponentId(); //With some template magic we're able to set a new unique id for each component type that gets registered. Really fancy stuff.

	template<typename T>
	void RegisterComponent(); //Simply registers a component.

	template<typename T, typename ... Args>
	void AddComponent(Entity entity, Args&& ... args); //Simply creates a component of type T for the specified entity. With perfect forwarding we're able to give it constructor arguments as well.

	template<typename T>
	void RemoveComponent(Entity entity); //Destroys a component of type T associated with the specified entity. 

	template<typename T>
	T* GetComponent(Entity entity); //returns GetComponent(entity) on the ComponentHandle of type T.

	template<typename T>
	T* GetSingleComponent(Entity entity); //returns GetSingleComponent(entity) on the ComponentHandle of type T.
};

template<typename T>
ComponentId ComponentManager::GetComponentId() {
	static ComponentId component_id = m_last_id++;
	return component_id;
}

template<typename T>
inline ComponentHandle<T>* ComponentManager::GetComponentHandle(ComponentId component_id) {
	return reinterpret_cast<ComponentHandle<T>*>(m_component_handles[component_id]);
}

template<typename T>
void ComponentManager::RegisterComponent() {
	ComponentHandle<T>* component_handle = new ComponentHandle<T>(m_alloc_chunk_size);
	component_handle->SetAllocationChunkSize(m_alloc_chunk_size);
	m_component_handles.insert(std::make_pair(GetComponentId<T>(), component_handle));
	//m_component_handles.emplace(GetComponentId<T>(), new ComponentHandle<T>());
}

template<typename T, typename ... Args>
void ComponentManager::AddComponent(Entity entity, Args&& ... args) {
	ComponentId component_id = GetComponentId<T>();
	ComponentHandle<T>* component_handle = GetComponentHandle<T>(component_id);
	component_handle->AddComponent(entity, std::forward<decltype(args)>(args) ...);
}

template<typename T>
void ComponentManager::RemoveComponent(Entity entity) {
	ComponentId component_id = GetComponentId<T>();
	ComponentHandle<T>* component_handle = GetComponentHandle<T>(component_id);
	component_handle->RemoveComponent(entity);
}

template<typename T>
T* ComponentManager::GetComponent(Entity entity) {
	ComponentId component_id = GetComponentId<T>();
	ComponentHandle<T>* component_handle = GetComponentHandle<T>(component_id);
	return component_handle->GetComponent(entity);
}

template<typename T>
T* ComponentManager::GetSingleComponent(Entity entity) {
	ComponentId component_id = GetComponentId<T>();
	ComponentHandle<T>* component_handle = GetComponentHandle<T>(component_id);
	return component_handle->GetSingleComponent(entity);
}