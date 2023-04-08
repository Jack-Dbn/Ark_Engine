#pragma once
#include <vector>
#include "GameEngine/Systems/RenderSystem.h"
#include "GameEngine/Systems/InputSystem.h"
#include "GameEngine/EntityManager.h"
#include "GameEngine/ComponentManager.h"
#include "GameEngine/Shapes.h"

namespace Ark {	

	class GameEngine
	{
	public:

		GameEngine();
		
		void Initialise(HWND windowHWND, std::wstring assetFolderPath = L"Debug/Assets/");

		void Update();

		void Release();

		void WindowResize(int newHeight, int newWidth);
		void KeyUp(int key);
		void KeyDown(int key);

		//App ECS Methods
		Ark::EntityManager* GetEC();

		Ark::Entity NewEntity();

		Ark::Model CreateModelEx(
			void* vtxArray,
			unsigned int vtxArraySize,
			unsigned int* idxArray,
			unsigned int idxArraySize);
		Ark::Model CreateModel(std::string filePath, bool CwWindingDir = false, bool LH_Convert = true);
		Ark::Material CreateMaterial(std::wstring textureFilePath);

		template <typename T>
		bool AddComponent(Ark::Entity tgtEntity);

		template <typename T>
		bool SetComponent(Ark::Entity tgtEntity, T newComponent);

		template <typename T>
		bool GetComponent(Ark::Entity tgtEntity, T& componentDest);

		template <typename T>
		bool RemoveComponent(Ark::Entity tgtEntity);		

	private:

		EntityManager m_entityController;
		ComponentManager m_componentManager;
		
		InputSystem m_inputSystem;
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


