#include <System.h>
#include <algorithm>

System::System() {

}

void System::EntityDestroyed(Entity entity) {
	auto it = std::lower_bound(m_entities.begin(), m_entities.end(), entity);

	if (it != m_entities.end() && *it == entity) {
		m_entities.erase(it);
	}
}

void System::SetSignature(Signature signature) {
	this->m_signature = signature;
}

void System::ComponentAdded(Entity entity, Signature entity_signature) {
	if ((entity_signature & m_signature) == m_signature) {
		auto it = std::lower_bound(m_entities.begin(), m_entities.end(), entity);

		if (it == m_entities.end() || *it != entity) {
			m_entities.insert(it, entity);
		}
	}
}

void System::ComponentRemoved(Entity entity, Signature entity_signature) {
	if ((entity_signature & m_signature) != m_signature) {
		auto it = std::lower_bound(m_entities.begin(), m_entities.end(), entity);

		if (it != m_entities.end() && *it == entity) {
			m_entities.erase(it);
		}
	}
}