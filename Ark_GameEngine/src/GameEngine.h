#pragma once
#include <vector>
#include "GameEngine/Systems/GraphicsSystem.h"
#include "GameEngine/Systems/InputSystem.h"
#include "GameEngine/Systems/GameLogicSystem.h"
#include "GameEngine/EntityManager.h"
#include "GameEngine/ComponentManager.h"
#include "GameEngine/Shapes.h"

namespace Ark {	

	class GameEngine
	{
	public:

		//Constructor
		GameEngine();
		
		//Engine Stages
		void Initialise(HWND windowHWND, std::wstring assetFolderPath = L"Assets/");

		void Update();

		void Release();

		//Engine Events
		void WindowResize(int newHeight, int newWidth);
		void KeyUp(int key);
		void KeyDown(int key);

		//App ECS Methods
		Ark::EntityManager* GetEC();

		Ark::Entity NewEntity();

		//Material & Model methods
		Ark::Model CreateModelEx(
			void* vtxArray,
			unsigned int vtxArraySize,
			unsigned int* idxArray,
			unsigned int idxArraySize);
		Ark::Model CreateModel(std::string filePath, bool CwWindingDir = false, bool LH_Convert = true);
		Ark::Material CreateMaterial(std::wstring textureFilePath);

		//Component CRUD methods
		template <typename T>
		bool AddComponent(Ark::Entity tgtEntity);

		template <typename T>
		bool SetComponent(Ark::Entity tgtEntity, T newComponent);

		template <typename T>
		bool GetComponent(Ark::Entity tgtEntity, T& componentDest);

		template <typename T>
		bool RemoveComponent(Ark::Entity tgtEntity);		

	private:
		//Engine Architecture
		EntityManager m_entityManager;
		ComponentManager m_componentManager;
		
		//Systems
		InputSystem m_inputSystem;
		GraphicsSystem m_graphicsSystem;
		GameLogicSystem m_gameplaySystem;

		//Delta time
		float m_deltaTime;
		DWORD m_lastTickCount;
		DWORD m_newTickCount;

		//Design Phase/Testing Phase boolean
		bool m_gameActive;
	};

	//Component CRUD - Template methods
	template<typename T>
	inline bool GameEngine::AddComponent(Ark::Entity tgtEntity)
	{
		T newComponent;
		bool res = m_componentManager.SetComponent<T>(tgtEntity, newComponent);

		res = res && m_entityManager.UpdateMask(tgtEntity, m_componentManager.GetBitPos<T>(), true);

		return res;
	}

	template<typename T>
	inline bool GameEngine::SetComponent(Ark::Entity tgtEntity, T newComponent)
	{
		bool res = m_componentManager.SetComponent<T>(tgtEntity, newComponent);
		res = res && m_entityManager.UpdateMask(tgtEntity, m_componentManager.GetBitPos<T>(), true);

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
		res = res && m_entityManager.UpdateMask(tgtEntity, m_componentManager.GetBitPos<T>(), false);

		return res;
	}
}


