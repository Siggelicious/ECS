#include <iostream>
#include <ComponentManagerBase.h>
#include <ComponentHandle.h>

struct Position {
	float x, y;
};

class ComponentManager : public ComponentManagerBase {
private:
	ComponentHandle* position_component;
public:
	ComponentManager() {
		position_component = RegisterComponent<Position>();
	}
};

int main() {

	return 0;
}