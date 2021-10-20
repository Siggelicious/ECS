#include <ComponentHandle.h>

template<typename T>
ComponentHandle<T>::ComponentHandle(uint32_t index) {
	this->index = index;
}