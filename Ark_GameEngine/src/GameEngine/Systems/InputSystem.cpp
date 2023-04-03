#include "InputSystem.h"

InputSystem::InputSystem()
{
}

int InputSystem::Initialise()
{
    designPreview = true;
    freeLookEnabled = false;

    return 0;
}

int InputSystem::Update(Ark::ComponentManager& engineCM)
{
    return 0;
}

int InputSystem::Release()
{
    return 0;
}

void InputSystem::KeyUp(int keyCode)
{
    if (designPreview) {
        switch (keyCode) {

        case VK_RBUTTON:
            freeLookEnabled = false;
            MessageBox(NULL, L"Camera Released", L"Camera Released", 0);
            return;
        }
    }
    
}

void InputSystem::KeyDown(int keyCode)
{
    if (designPreview) {
        switch (keyCode) {

            case VK_SPACE:
                designPreview = false;
                MessageBox(NULL, L"Game Started", L"Game Started", 0);
                return;

            case VK_RBUTTON:
                freeLookEnabled = true;
                return;
        }
    }   

    if (keyCode == VK_ESCAPE) {
        designPreview = true;
        MessageBox(NULL, L"Game Stopped", L"Game Stopped", 0);
        return;
    }
}
