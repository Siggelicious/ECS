#pragma once
#include <cstdint>

class ComponentHandle {
private:
	uint32_t index;
public:
	ComponentHandle(uint32_t index);
};