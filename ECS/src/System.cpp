#include <System.h>
#include <algorithm>

System::System() {

}

void System::EntityDestroyed(Entity entity) {
	auto it = std::lower_bound(entities.begin(), entities.end(), entity);

	if (it != entities.end() && *it == entity) {
		entities.erase(it);
	}
}

void System::SetSignature(Signature signature) {
	this->signature = signature;
}

void System::ComponentAdded(Entity entity, Signature entity_signature) {
	if ((entity_signature & signature) == signature) {
		auto it = std::lower_bound(entities.begin(), entities.end(), entity);

		if (it == entities.end() || *it != entity) {
			entities.insert(it, entity);
		}
	}
}

void System::ComponentRemoved(Entity entity, Signature entity_signature) {
	if ((entity_signature & signature) != signature) {
		auto it = std::lower_bound(entities.begin(), entities.end(), entity);

		if (it != entities.end() && *it == entity) {
			entities.erase(it);
		}
	}
}