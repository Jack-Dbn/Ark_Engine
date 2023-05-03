#include "GameEngine.h"

namespace Ark {
	GameEngine::GameEngine()
	{
	}

	void GameEngine::Initialise(HWND windowHWND, std::wstring assetFolderPath)
	{
		m_deltaTime = 0.0f;
		m_lastTickCount = 0;
		m_newTickCount = 0;

		m_gameActive = false;

		//Register components to use in the engine.
		m_componentManager.RegisterComponent<Transform>();	
		m_componentManager.RegisterComponent<Model>();
		m_componentManager.RegisterComponent<Material>();
		m_componentManager.RegisterComponent<InputRig>();
		m_componentManager.RegisterComponent<GameRole>();

		m_graphicsSystem.SetParam(windowHWND, assetFolderPath);
		m_graphicsSystem.Initialise(&m_gameActive);
		{
			m_graphicsSystem.AddReqComponent<Transform>(m_componentManager.GetRegister());
			m_graphicsSystem.AddReqComponent<Model>(m_componentManager.GetRegister());
			m_graphicsSystem.AddReqComponent<Material>(m_componentManager.GetRegister());
		}

		m_inputSystem.SetCamera(m_graphicsSystem.GetCamera());
		m_inputSystem.SetDeltaTime(&m_deltaTime);
		m_inputSystem.Initialise(&m_gameActive);
		{
			m_inputSystem.AddReqComponent<Transform>(m_componentManager.GetRegister());
			m_inputSystem.AddReqComponent<InputRig>(m_componentManager.GetRegister());
		}

		m_gameplaySystem.Initialise(&m_gameActive);
		{
			m_gameplaySystem.AddReqComponent<Transform>(m_componentManager.GetRegister());
			m_gameplaySystem.AddReqComponent<GameRole>(m_componentManager.GetRegister());
		}
		
		//Gui
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();

		// Setup Platform/Renderer backends
		ImGui_ImplWin32_Init(windowHWND);
		ImGui_ImplDX11_Init(m_graphicsSystem.GetDevice(), m_graphicsSystem.GetDeviceContext());

		m_selectedEntity = 0;

		wchar_t text[256];

		swprintf_s(text, L"Registered Components: %d", m_componentManager.GetRegisterCount());
		MessageBox(NULL, text, text, 0);
		
	}

	void GameEngine::Update()
	{	
		//Delta time calculation
		m_lastTickCount = m_newTickCount;
		m_newTickCount = ::GetTickCount();

		m_deltaTime = (m_newTickCount - m_lastTickCount) / 1000.0f;		

		//Gameplay System
		std::vector<Ark::Entity> sysEntities = m_entityManager.EvalSysEntities(m_gameplaySystem.GetFilterMask());
		m_gameplaySystem.SetEntityList(sysEntities);

		m_gameplaySystem.Update(m_componentManager);

		//Input System
		sysEntities = m_entityManager.EvalSysEntities(m_inputSystem.GetFilterMask());
		m_inputSystem.SetEntityList(sysEntities);

		m_inputSystem.Update(m_componentManager);

		//Gui
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		if (!m_gameActive) {
			GuiEntityWindow();	
			GuiComponentWindow();
		}		

		//Render System
		sysEntities = m_entityManager.EvalSysEntities(m_graphicsSystem.GetFilterMask());
		m_graphicsSystem.SetEntityList(sysEntities);

		m_graphicsSystem.Update(m_componentManager);
	}

	void GameEngine::Release()
	{
		// Cleanup
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();

		m_gameplaySystem.Release();
		m_inputSystem.Release();
		m_graphicsSystem.Release();
	}

	void GameEngine::WindowResize(int newHeight, int newWidth)
	{
		m_graphicsSystem.Resize(newHeight, newWidth);
	}

	void GameEngine::KeyUp(int key)
	{
		m_inputSystem.KeyUp(key);
	}

	void GameEngine::KeyDown(int key)
	{
		m_inputSystem.KeyDown(key);
	}

	Ark::EntityManager* GameEngine::GetEC()
	{
		return &m_entityManager;
	}

	Ark::Entity GameEngine::NewEntity()
	{
		return m_entityManager.NewEntity();
	}

	Ark::Model GameEngine::CreateModelEx(void* vtxArray,
		unsigned int vtxArraySize,
		unsigned int* idxArray,
		unsigned int idxArraySize)
	{
		return m_graphicsSystem.CreateDxModelEx(vtxArray, vtxArraySize, idxArray, idxArraySize);
	}

	Ark::Model GameEngine::CreateModel(std::string filePath, bool CwWindingDir, bool LH_Convert)
	{
		return m_graphicsSystem.CreateDxModel(filePath, CwWindingDir, LH_Convert);
	}

	Ark::Material GameEngine::CreateMaterial(std::wstring textureFilePath)
	{
		return m_graphicsSystem.CreateMaterial(textureFilePath);
	}

	//Gui elements
	void GameEngine::GuiEntityWindow()
	{
		ImGui::Begin("Entities");

		//New Entity Button
		if (ImGui::Button("New Entity")) {
			this->NewEntity();
		}

		std::vector<Ark::Entity> activeEntityList = m_entityManager.GetActiveEntityList();
		//Entity List
		if (ImGui::BeginTable("Entity ID", 1)) {
			for (int n = 0; n < activeEntityList.size(); n++) {
				ImGui::TableNextRow();
				ImGui::TableNextColumn();
				//ImGui::Text(("Entity: " + std::to_string(activeEntityList[n])).c_str());
				ImGuiSelectableFlags flags = ImGuiSelectableFlags_None;
				
				
				if (ImGui::Selectable(std::to_string(activeEntityList[n]).c_str(), false, flags))
				{
					m_selectedEntity = activeEntityList[n];
				}

			}
			ImGui::EndTable();
		}
			
		

		ImGui::End();
	}
	void GameEngine::GuiComponentWindow()
	{
		ImGui::Begin("Components");
		ImGui::Text(std::to_string(m_selectedEntity).c_str());

		ImGui::End();
	}
}