#include <System.h>
#include <algorithm>

System::System() {
	num_entities = 0;
}

void System::AddEntity(Entity entity) {
	entities.push_back(entity);
	entity_to_index.insert(std::make_pair(entity, num_entities));
	num_entities++;
}

void System::RemoveEntity(Entity entity) {
	size_t index = entity_to_index[entity];

	for (auto& pair : entity_to_index) {
		if (pair.second > index) {
			pair.second--;
		}
	}

	entities.erase(entities.begin() + index);
	entity_to_index.erase(entity);
	num_entities--;
}

void System::EntityDestroyed(Entity entity) {
	if (entity_to_index.find(entity) != entity_to_index.end()) {
		RemoveEntity(entity);
	}
}

void System::SetSignature(Signature signature) {
	this->signature = signature;
}

void System::EntitySignatureChanged(Entity entity, Signature entity_signature) {
	bool has_entity = entity_to_index.find(entity) != entity_to_index.end();

	if ((entity_signature & signature) == signature) {
		if (!has_entity) {
			AddEntity(entity);
		}
	}

	else {
		if (has_entity) {
			RemoveEntity(entity);
		}
	}
}