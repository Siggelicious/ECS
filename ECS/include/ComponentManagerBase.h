#pragma once
#include <Entity.h>
#include <vector>
#include <ComponentHandle.h>

class ComponentManagerBase {
private:
	uint32_t num_components;
	std::vector<AComponentHandle*> component_handles;
public:
	template<typename T>
	ComponentHandle<T>* RegisterComponent();

	virtual ~ComponentManagerBase();
};