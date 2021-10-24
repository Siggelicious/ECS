#pragma once
#include <Types.h>

class AComponentHandle {
public:
	virtual void EntityDestroyed(Entity entity) = 0;
	virtual ~AComponentHandle() = default;
};