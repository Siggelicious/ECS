#pragma once
#include <Types.h>
#include <vector>
#include <unordered_set>
#include <unordered_map>

class System {
private:
	Signature signature;
	std::unordered_map<Entity, size_t> entity_to_index;
	
	void AddEntity(Entity entity);
	void RemoveEntity(Entity entity);
public:
	std::vector<Entity> entities;
	virtual ~System() = default;
	virtual void Update() = 0;
	void EntityDestroyed(Entity entity);
	void SetSignature(Signature signature);
	void EntitySignatureChanged(Entity entity, Signature entity_signature);
};