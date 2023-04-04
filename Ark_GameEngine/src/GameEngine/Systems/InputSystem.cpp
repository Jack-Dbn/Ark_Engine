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
    m_freeLookEnabled = false;

    if (!m_engineCamera) {
        return -1;
    }

    return 0;
}

int InputSystem::Update(Ark::ComponentManager& engineCM)
{
    if (m_a) {
        Ark::matrix4x4 tmp('i');
        tmp = tmp.TranslateMtx(0.05f, 0.0f, 0.0f);
        m_engineCamera->m_view = tmp * m_engineCamera->m_view;
    }
    if (m_d) {
        Ark::matrix4x4 tmp('i');
        tmp = tmp.TranslateMtx(-0.05f, 0.0f, 0.0f);
        m_engineCamera->m_view = tmp * m_engineCamera->m_view;
    }
    if (m_w) {
        Ark::matrix4x4 tmp('i');
        tmp = tmp.TranslateMtx(0.0f, 0.0f, 0.05f);
        m_engineCamera->m_view = tmp * m_engineCamera->m_view;
    }
    if (m_s) {
        Ark::matrix4x4 tmp('i');
        tmp = tmp.TranslateMtx(0.0f, 0.0f, -0.05f);
        m_engineCamera->m_view = tmp * m_engineCamera->m_view;
    }
    if (m_space) {
        Ark::matrix4x4 tmp('i');
        tmp = tmp.TranslateMtx(0.0f, -0.05f, 0.0f);
        m_engineCamera->m_view = tmp * m_engineCamera->m_view;
    }
    if (m_shift) {
        Ark::matrix4x4 tmp('i');
        tmp = tmp.TranslateMtx(0.0f, 0.05f, 0.0f);
        m_engineCamera->m_view = tmp * m_engineCamera->m_view;
    }

    return 0;
}

int InputSystem::Release()
{
    return 0;
}

void InputSystem::KeyUp(int keyCode)
{
    if (m_designPreview) {
        switch (keyCode) {

        case VK_RBUTTON:
            m_freeLookEnabled = false;
            MessageBox(NULL, L"Camera Released", L"Camera Released", 0);
            return;

        case 'W':
            m_w = false;
            return;

        case 'A':
            m_a = false;
            return;

        case 'S':
            m_s = false;
            return;

        case 'D':
            m_d = false;
            return;

        case VK_SPACE:
            m_space = false;
            return;

        case VK_SHIFT:
            m_shift = false;
            return;
        }
    }
    
}

void InputSystem::KeyDown(int keyCode)
{
    if (m_designPreview) {
        switch (keyCode) {

            case 'P':
                m_designPreview = false;
                MessageBox(NULL, L"Game Started", L"Game Started", 0);
                return;

            case VK_RBUTTON:
                m_freeLookEnabled = true;
                return;

            case 'W':
                m_w = true;
                return;

            case 'A':
                m_a = true;
                return;

            case 'S':
                m_s = true;
                return;

            case 'D':
                m_d = true;
                return;

            case VK_SPACE:
                m_space = true;
                return;

            case VK_SHIFT:
                m_shift = true;
                return;
        }
    }   

    if (keyCode == VK_ESCAPE) {
        m_designPreview = true;
        MessageBox(NULL, L"Game Stopped", L"Game Stopped", 0);
        return;
    }
}
