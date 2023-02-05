#pragma once
#include <vector>
#include "GameEngine/Systems/RenderSystem.h"
#include "GameEngine/Components/Transform.h"
#include "GameEngine/Components/Model.h"
#include "GameEngine/Components/Material.h"
#include "GameEngine/EntityController.h"
#include "GameEngine/ComponentManager.h"

namespace Ark {	

	class GameEngine
	{
	public:

		GameEngine();
		
		void Initialise(HWND windowHWND, std::wstring assetFolderPath = L"Debug/Assets/");

		void Update();

		void Release();

		void WindowResize(int newHeight, int newWidth);

		//App ECS Methods
		Ark::EntityController* GetEC();

		Ark::Entity NewEntity();

		template <typename T>
		bool AddComponent(Ark::Entity tgtEntity);

		template <typename T>
		bool SetComponent(Ark::Entity tgtEntity, T newComponent);

		template <typename T>
		bool GetComponent(Ark::Entity tgtEntity, T& componentDest);

		template <typename T>
		bool RemoveComponent(Ark::Entity tgtEntity);

	private:
		std::vector<System> m_activeSystems;

		EntityController m_entityController;
		ComponentManager m_componentManager;

		RenderSystem m_renderSystem;
	};

	template<typename T>
	inline bool GameEngine::AddComponent(Ark::Entity tgtEntity)
	{
		T newComponent;
		bool res = m_componentManager.SetComponent<T>(tgtEntity, newComponent);

		res = res && m_entityController.UpdateMask(tgtEntity, m_componentManager.GetBitPos<T>(), true);

		return res;
	}

	template<typename T>
	inline bool GameEngine::SetComponent(Ark::Entity tgtEntity, T newComponent)
	{
		bool res = m_componentManager.SetComponent<T>(tgtEntity, newComponent);
		res = res && m_entityController.UpdateMask(tgtEntity, m_componentManager.GetBitPos<T>(), true);

		return res;
	}

	template<typename T>
	inline bool GameEngine::GetComponent(Ark::Entity tgtEntity, T& componentDest)
	{
		return m_componentManager.GetComponent<T>(tgtEntity, componentDest);
	}

	template<typename T>
	inline bool GameEngine::RemoveComponent(Ark::Entity tgtEntity)
	{
		bool res = m_componentManager.RemoveComponent<T>(tgtEntity);
		res = res && m_entityController.UpdateMask(tgtEntity, m_componentManager.GetBitPos<T>(), false);

		return res;
	}
}


