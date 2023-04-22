#include "InputSystem.h"

InputSystem::InputSystem()
{
}

bool InputSystem::SetCamera(Ark::Camera* camera)
{
    if (camera) {
        m_engineCamera = camera;
        return true;
    }

    return false;
}

bool InputSystem::SetDeltaTime(float* deltaTimePtr)
{
    if (deltaTimePtr) {
        m_engineDeltaTime = deltaTimePtr;
        return true;
    }

    return false;
}

int InputSystem::Initialise()
{
    m_designPreview = true;
    m_screenHeight = GetSystemMetrics(SM_CYSCREEN);
    m_screenWidth = GetSystemMetrics(SM_CXSCREEN);

    m_mouseSensitivity = 10.0f;
    m_cameraSpeed = 75.0f;

    if (!m_engineCamera) {
        return -1;
    }

    if (!m_engineDeltaTime) {
        return -2;
    }

    return 0;
}

int InputSystem::Update(Ark::ComponentManager& engineCM)
{
    if (m_designPreview) {

        for (const auto& key : m_keyMap) {
            if (key.second) {                
                PreviewInput(key.first);
            }
        }        
    }
    else {
        for (const auto& key : m_keyMap) {
            if (key.second) {                
                GameInput(key.first);
            }
        }
    }

    if (m_designPreview && m_keyMap[VK_RBUTTON]) {
        POINT cursorPos = {};
        ::GetCursorPos(&cursorPos);

        int screenCentreX = m_screenWidth / 2;
        int screenCentreY = m_screenHeight / 2;

        if (screenCentreX != cursorPos.x || screenCentreY != cursorPos.y) {

            float cameraYawDelta = (cursorPos.x - screenCentreX) * (*m_engineDeltaTime) * m_mouseSensitivity;
            float cameraPitchDelta = (cursorPos.y - screenCentreY) * (*m_engineDeltaTime) * m_mouseSensitivity;

            m_engineCamera->Rotate(cameraPitchDelta, cameraYawDelta);

            ::SetCursorPos(m_screenWidth / 2, m_screenHeight / 2);
        }      
    }  

    return 0;
}

int InputSystem::Release()
{
    return 0;
}

void InputSystem::KeyUp(int keyCode)
{
    m_keyMap[keyCode] = false;    
}

void InputSystem::KeyDown(int keyCode)
{
    m_keyMap[keyCode] = true;
}

void InputSystem::PreviewInput(int keyCode)
{
    switch (keyCode) {
        case 'P':
            if (m_designPreview) {
                m_designPreview = false;
                MessageBox(NULL, L"Game Started", L"Game Started", 0);
                m_keyMap[keyCode] = false;
            }            
            return;

        case 'W':
            if (m_keyMap[VK_RBUTTON]) {
                float deltaPosZ = (*m_engineDeltaTime) * m_cameraSpeed * 0.05f;
                m_engineCamera->Translate(0.0f, 0.0f, deltaPosZ);
            }
            return;

        case 'A':
            if (m_keyMap[VK_RBUTTON]) {
                float deltaPosX = (*m_engineDeltaTime) * m_cameraSpeed * 0.05f;
                m_engineCamera->Translate(deltaPosX, 0.0f, 0.0f);
            }
            return;

        case 'S':
            if (m_keyMap[VK_RBUTTON]) {
                float deltaPosZ = (*m_engineDeltaTime) * m_cameraSpeed * -0.05f;
                m_engineCamera->Translate(0.0f, 0.0f, deltaPosZ);
            }
            return;

        case 'D':
            if (m_keyMap[VK_RBUTTON]) {
                float deltaPosX = (*m_engineDeltaTime) * m_cameraSpeed * -0.05f;
                m_engineCamera->Translate(deltaPosX, 0.0f, 0.0f);
            }
            return;

        case VK_SPACE:
            if (m_keyMap[VK_RBUTTON]) {
                float deltaPosY = (*m_engineDeltaTime) * m_cameraSpeed * -0.05f;
                m_engineCamera->Translate(0.0f, deltaPosY, 0.0f);
            }
            return;

        case VK_SHIFT:
            if (m_keyMap[VK_RBUTTON]) {
                float deltaPosY = (*m_engineDeltaTime) * m_cameraSpeed * 0.05f;
                m_engineCamera->Translate(0.0f, deltaPosY, 0.0f);
            }
            return;
    }
}

void InputSystem::GameInput(int keyCode)
{
    switch (keyCode) {
        case VK_ESCAPE:
            if (!m_designPreview) {
                m_designPreview = true;
                MessageBox(NULL, L"Game Stopped", L"Game Stopped", 0);
                m_keyMap[keyCode] = false;
            }            
            return;
    }
}