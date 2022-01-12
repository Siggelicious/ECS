#pragma once
#include <queue>
#include <unordered_map>
#include <Types.h>

/* 
Creates entities and manages the entitiy signatures.
*/

class EntityManager {
private:
	Entity m_last_entity; //Keeps track of the highest entity ID ever created in case m_destroyed_entities is empty.
	std::queue<Entity> m_destroyed_entities; //Stores all the destroyed entity IDs to be reused.
	std::unordered_map<Entity, Signature> m_signatures; //Just an unordered_map for quick signature retrieval. 
public:
	EntityManager(); //Inits.
	Entity CreateEntity(); //Creates an entity, either m_last_entity++ or m_destroyed_entities.front(). 
	void DestroyEntity(Entity entity); //Pushes the entity onto the m_destroyed_entities queue to be reused.
	void SetSignature(Entity entity, ComponentId component_id, bool value); //Sets the entity signature in m_signatures.
	Signature GetSignature(Entity entity); //Retrieves the signature for the specified entity.
};