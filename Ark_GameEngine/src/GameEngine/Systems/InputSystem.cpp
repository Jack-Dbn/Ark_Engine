#include "InputSystem.h"

InputSystem::InputSystem()
{
}

bool InputSystem::SetCamera(Ark::ConstantBuffer* camera)
{
    if (camera) {
        m_engineCamera = camera;
        return true;
    }

    return false;
}

int InputSystem::Initialise()
{
    m_designPreview = true;

    if (!m_engineCamera) {
        return -1;
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
                TranslateCamera(0.0f, 0.0f, 0.05f);
            }
            return;

        case 'A':
            if (m_keyMap[VK_RBUTTON]) {
                TranslateCamera(0.05f, 0.0f, 0.0f);
            }
            return;

        case 'S':
            if (m_keyMap[VK_RBUTTON]) {
                TranslateCamera(0.0f, 0.0f, -0.05f);
            }
            return;

        case 'D':
            if (m_keyMap[VK_RBUTTON]) {
                TranslateCamera(-0.05f, 0.0f, 0.0f);
            }
            return;

        case VK_SPACE:
            if (m_keyMap[VK_RBUTTON]) {
                TranslateCamera(0.0f, -0.05f, 0.0f);
            }
            return;

        case VK_SHIFT:
            if (m_keyMap[VK_RBUTTON]) {
                TranslateCamera(0.0f, 0.05f, 0.0f);
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

void InputSystem::TranslateCamera(float x, float y, float z)
{
    Ark::matrix4x4 tmp('i');
    tmp = tmp.TranslateMtx(x, y, z);
    m_engineCamera->m_view = tmp * m_engineCamera->m_view;
}
