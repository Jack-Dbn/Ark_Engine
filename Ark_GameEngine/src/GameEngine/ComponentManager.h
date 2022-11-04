#pragma once
#include <typeinfo>
#include "EntityController.h"

namespace Ark {
	class ComponentManager
	{
	public:
		//ComponentManager();

		template <typename T>
		bool RegisterComponent();

		bool AddComponent(Ark::Entity tgtEntity, Ark::Component newComponent);

	
	};

	template<typename T>
	inline bool ComponentManager::RegisterComponent()
	{
		const char* typeName = typeid(T).name();
		return false;
	}
}


