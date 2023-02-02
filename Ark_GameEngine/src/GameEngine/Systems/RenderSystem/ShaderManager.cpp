#include "ShaderManager.h"

Ark::ShaderManager::ShaderManager() {

}

bool Ark::ShaderManager::SetShaderPath(std::wstring shaderPath)
{
    m_shaderFolder = shaderPath.c_str();
       
    //TO DO: Check folder contains a pixel and vertex shader.

    return true;
}
