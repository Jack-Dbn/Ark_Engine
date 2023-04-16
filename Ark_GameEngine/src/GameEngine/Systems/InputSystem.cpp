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

    m_mouseSensitivity = 0.1f;

    m_cameraYaw = 0.0f;
    m_cameraPitch = 0.0f;

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

    if (m_keyMap[VK_RBUTTON]) {
        POINT cursorPos = {};
        ::GetCursorPos(&cursorPos);

        int screenCentreX = m_screenWidth / 2;
        int screenCentreY = m_screenHeight / 2;

        if (screenCentreX != cursorPos.x || screenCentreY != cursorPos.y) {

            m_cameraYaw += (cursorPos.x - screenCentreX) * (*m_engineDeltaTime) * m_mouseSensitivity;
            m_cameraPitch += (cursorPos.y - screenCentreY) * (*m_engineDeltaTime) * m_mouseSensitivity;

            RotateCamera(m_cameraYaw, m_cameraPitch);

            ::SetCursorPos(m_screenWidth / 2, m_screenHeight / 2);

            if (m_cameraPitch > -90.0f || m_cameraPitch < 90.0f) {
                m_cameraPitch = 0.0f;
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

void InputSystem::RotateCamera(float yaw, float pitch)
{
    Ark::matrix4x4 newViewMtx('i');

    newViewMtx = newViewMtx.RotateYmtx(yaw);
    newViewMtx = newViewMtx * newViewMtx.RotateXmtx(pitch);

    m_engineCamera->m_view = newViewMtx * m_engineCamera->m_view;
}
