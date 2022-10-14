#include "Entity.h"

namespace Ark {

	Entity::Entity() {
		MessageBox(NULL, L"Construct", L"Construct", 0);
		//m_id = -1;
	}

	Entity::~Entity()
	{	
		MessageBox(NULL, L"Destruct", L"Destruct", 0);
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

	void Entity::Load()
	{
		if (m_id != -1) {
			return;//Already Loaded
		}

		m_id = freeEntitySlots.back();
		freeEntitySlots.pop_back();


		wchar_t text[256];

		swprintf_s(text, L"Created entity with id: %d", m_id);
		MessageBox(NULL, text, text, 0);
		/*
		swprintf_s(text, L"Next Entity Id: %d", freeEntitySlots.back());
		MessageBox(NULL, text, text, 0);*/

		activeEntities.push_back(*this);
	}

	void Entity::Unload()
	{
		if (m_id == -1) {
			return;//Already Unloaded
		}

		activeEntities.erase(activeEntities.begin()+m_id);

		wchar_t text[256];

		swprintf_s(text, L"Returning entity id: %d", m_id);
		MessageBox(NULL, text, text, 0);

		freeEntitySlots.push_back(m_id);

		m_id = -1;
	}
}