#pragma once
#include <Types.h>
#include <vector>
#include <unordered_set>
#include <unordered_map>

class Registry;

class System {
private:
	Signature signature;
public:
	std::vector<Entity> entities;
	System();
	virtual ~System() = default;
	void EntityDestroyed(Entity entity);
	void SetSignature(Signature signature);
	void ComponentAdded(Entity entity, Signature entity_signature);
	void ComponentRemoved(Entity entity, Signature entity_signature);
};