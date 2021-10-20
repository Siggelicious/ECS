#pragma once
#include <AComponentHandle.h>
#include <cstdint>
#include <map>
#include <Entity.h>
#include <unordered_map>

template<typename T>
class ComponentHandle : public AComponentHandle {
private:
	uint32_t index;
	std::unordered_map<Entity, T> components;
public:
	ComponentHandle(uint32_t index);
};