#pragma once
#include <AComponentHandle.h>
#include <cstdint>

template<typename T>
class ComponentHandle : public AComponentHandle {
private:
	uint32_t index;
public:
	ComponentHandle(uint32_t index);
};