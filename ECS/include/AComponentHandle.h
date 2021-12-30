#pragma once
#include <Types.h>

class AComponentHandle {
public:
	uint32_t m_alloc_chunk_size;

	virtual void EntityDestroyed(Entity entity) = 0;
	virtual ~AComponentHandle() = default;
	void SetAllocationChunkSize(uint32_t alloc_chunk_size);
};