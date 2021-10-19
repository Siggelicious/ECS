#pragma once
#include <Entity.h>
#include <vector>
#include <ComponentHandle.h>

class ComponentManagerBase {
private:
	uint32_t num_components;
	std::vector<ComponentHandle*> component_handles;
public:
	ComponentHandle* RegisterComponent();

	virtual ~ComponentManagerBase();
};