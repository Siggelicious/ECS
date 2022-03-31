#pragma once
#include <Types.h>
#include <vector>
#include <unordered_set>
#include <unordered_map>

class Registry;

class System {
private:
	std::vector<Entity> m_entities; //A sorted vector to keep track of which entites are being operated on by a system. //dbg
	Signature m_signature; //The system signature, to compare against the entity signature.
public:
	System(); //Default.
	virtual ~System() = default;
	const std::vector<Entity>& GetEntities(); //An inline function that returns a const reference of m_entities to be used in the systems update function.
	void EntityDestroyed(Entity entity); //Removes the entity from m_entities if it's found.
	void SetSignature(Signature signature); //Sets m_signature.
	void ComponentAdded(Entity entity, Signature entity_signature); //Gets broadcasted to all systems when Registry::AddComponent is called. Checks to see if the entity signature matches the system signature, and if so, adds it to m_entities.
	void ComponentRemoved(Entity entity, Signature entity_signature); //Gets broadcasted to all systems when Registry::RemoveComponent is called. Checks to see if the entity signature still matches the system signature, if it ever did, and if not removes it.
};