#pragma once
#include <Types.h>

/*
This is an abstract class (cleverly prefixed with A) and should never be used directly in anyway by the developer.
It is actually pretty unnecessary, since I reinterpret_cast everything later on anyway but logically speaking it makes sense.
By having this class being abstract, we can call some functions without having to cast, which makes things a bit easier to read in code and really should not affect performance what so ever.
For instance, SetAllocationChunkSize()
*/


class AComponentHandle {
public:
	uint32_t m_alloc_chunk_size; /*
								 This is just the member variable used to keep track of the allocation chunk size.
								 I decided every component handle should have a unique variable, in case I ever wanted to implement per component allocation chunk size.
								 */

	virtual void EntityDestroyed(Entity entity) = 0; //Gets called if a entity is destroyed.
	virtual ~AComponentHandle() = default; //Does nothing.
	void SetAllocationChunkSize(uint32_t alloc_chunk_size); //Literally just sets m_alloc_chunk_size.
};