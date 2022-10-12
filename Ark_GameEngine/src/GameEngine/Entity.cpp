#include "Entity.h"

namespace Ark {

	Entity::Entity() {
		m_id = freeEntitySlots.back();
		freeEntitySlots.pop_back();

		wchar_t text[256];

		swprintf_s(text, L"Created entity two: %d", m_id);
		MessageBox(NULL, text, text, 0);
	}

	Entity::~Entity()
	{
		wchar_t text[256];

		swprintf_s(text, L"Deleting entity: %d", m_id);
		MessageBox(NULL, text, text, 0);

		freeEntitySlots.push_back(m_id);
	}

	void Entity::Initialise(unsigned int maxEntities)
	{
		if (freeEntitySlots.size() > 0) {
			freeEntitySlots.clear();
		}

		for (int i = (maxEntities - 1); i >= 0; i--) {
			freeEntitySlots.push_back(i);
		}
	}
}