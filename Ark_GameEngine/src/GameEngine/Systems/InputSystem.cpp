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

int InputSystem::Initialise(bool* isGameRunning)
{
    m_gameActive = isGameRunning;

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
    /*
    //If in design stage...
    if (!*m_gameActive) {
        //Iterate through keys in keymap
        for (const auto& key : m_keyMap) {

            //If key active and not 'P'
            if (key.second && key.first != 'P') {
                PreviewInput(key.first);
            }
            //if key is 'P' and active
            else if (key.second && key.first == 'P') {

                //Save intial transforms.
                engineCM.SaveTransforms();

                //Switch engine to testing stage.
                *m_gameActive = true;

                //Notify user the testing has begun.
                MessageBox(NULL, L"Game Started", L"Game Started", 0);

                //Clear keymap as preview inputs not needed anymore.
                m_keyMap.clear();

                //Ensures no more design stage inputs are processed this tick.
                return 0;
            }
        }        
    }
    else {
        for (const auto& key : m_keyMap) {
            if (key.second && key.first != VK_ESCAPE) {
                GameInput(key.first, engineCM);
            }
            else if (key.second && key.first == VK_ESCAPE) {

                engineCM.LoadTransforms();

                *m_gameActive = false;
                MessageBox(NULL, L"Game Stopped", L"Game Stopped", 0);

                m_keyMap.clear();
                return 0;
            }
        }
    }*/

    //Iterate through to find pressed keys...
    for (const auto& key : m_keyMap) {
        //Design phase
        if (!*m_gameActive && key.second && key.first != 'P') {
            //Process key for design phase normally.
            PreviewInput(key.first);
        }
        else if (!*m_gameActive && key.second && key.first == 'P') {
            //Save intial transforms.
            engineCM.SaveTransforms();

            //Switch engine to testing stage.
            *m_gameActive = true;

            //Notify user the testing has begun.
            MessageBox(NULL, L"Game Started", L"Game Started", 0);

            //Clear keymap as preview inputs not needed anymore.
            m_keyMap.clear();

            //Ensures no more design stage inputs are processed this tick.
            return 0;
        }
        //Testing phase
        else if (*m_gameActive && key.second && key.first != VK_ESCAPE) {
            //Proces key for game normally.
            GameInput(key.first, engineCM);
        }
        else if (*m_gameActive && key.second && key.first == VK_ESCAPE) {
            //Load transforms that were saved at the end of design phase.
            engineCM.LoadTransforms();

            //Switch engine to design phase.
            *m_gameActive = false;

            //Notify user game has stopped.
            MessageBox(NULL, L"Game Stopped", L"Game Stopped", 0);

            //Clear key map as testing inputs are not valid anymore.
            m_keyMap.clear();

            //Exit update to ensure no more testing keys are processed.
            return 0;
        }
    }

    //If in design stage and right click is being held...
    if (!*m_gameActive && m_keyMap[VK_RBUTTON]) {

        //Create Point object to store cursor position.
        POINT cursorPos = {};
        //Fill object with current cursor position.
        ::GetCursorPos(&cursorPos);

        //Find x and y coordinates of screen's centre point.
        int screenCentreX = m_screenWidth / 2;
        int screenCentreY = m_screenHeight / 2;

        //If cursor is not centred...
        if (screenCentreX != cursorPos.x || screenCentreY != cursorPos.y) {

            //Use offset from centre to calculate how much to change the yaw and pitch.
            float cameraYawDelta = (cursorPos.x - screenCentreX) * (*m_engineDeltaTime) * m_mouseSensitivity;
            float cameraPitchDelta = (cursorPos.y - screenCentreY) * (*m_engineDeltaTime) * m_mouseSensitivity;

            //Rotate engine's camera with these new values.
            m_engineCamera->Rotate(cameraPitchDelta, cameraYawDelta);

            //Re-centre cursor.
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

void InputSystem::GameInput(int keyCode, Ark::ComponentManager& engineCM)
{
    //Iterate through entities with a transform and input rig...
    for (int i = 0; i < m_EntityList.size(); i++) {

        //Note current entity id.
        Ark::Entity entityIn = m_EntityList[i];

        //Get transform of entity.
        Ark::Transform entityTransform;
        engineCM.GetComponent<Ark::Transform>(entityIn, entityTransform);

        //Get input rig of entity.
        Ark::InputRig entityInputRig;
        engineCM.GetComponent<Ark::InputRig>(entityIn, entityInputRig);

        //Get entitiy's keymap
        std::unordered_map<char, Ark::Action> rigKeyMap = entityInputRig.GetKeyMap();

        //Iterate through each key in input rig.
        for (const auto& rigKey : rigKeyMap) {

            //If a input-rig key matches the pressed key...
            if (rigKey.first == keyCode) {

                //Store action for that key code
                Ark::Action action = rigKey.second;

                //Store input sizes for x,y,z.
                float deltaX = 0.0f, deltaY = 0.0f, deltaZ = 0.0f;
                if (action.axis == Ark::x) {
                    deltaX = action.inputSize;
                }
                else if (action.axis == Ark::y) {
                    deltaY = action.inputSize;
                }
                else {
                    deltaZ = action.inputSize;
                }

                //Apply action to transform.
                if (action.action == Ark::Position) {
                    entityTransform.Translate(deltaX, deltaY, deltaZ);
                }
                else if (action.action == Ark::Rotation) {
                    entityTransform.Rotate(deltaX, deltaY, deltaZ);
                }
                else {
                    entityTransform.Resize(deltaX, deltaY, deltaZ);
                }

                //Update entity with updated transform.
                engineCM.SetComponent<Ark::Transform>(entityIn, entityTransform);

                break;
            }
        }
    }
}

