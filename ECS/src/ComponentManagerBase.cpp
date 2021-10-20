#include <ComponentManagerBase.h>

template<typename T>
ComponentHandle<T>* ComponentManagerBase::RegisterComponent() {
	ComponentHandle<T>* component_handle = new ComponentHandle<T>(num_components++);
	component_handles.push_back(component_handle);
	return component_handle;
}

ComponentManagerBase::~ComponentManagerBase() {
	for (auto component_handle : component_handles) {
		delete component_handle;
	}
}