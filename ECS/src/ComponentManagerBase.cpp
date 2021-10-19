#include <ComponentManagerBase.h>

ComponentHandle* ComponentManagerBase::RegisterComponent() {
	ComponentHandle* component_handle = new ComponentHandle(num_components++);
	component_handles.push_back(component_handle);
	return component_handle;
}

ComponentManagerBase::~ComponentManagerBase() {
	for (auto component_handle : component_handles) {
		delete component_handle;
	}
}