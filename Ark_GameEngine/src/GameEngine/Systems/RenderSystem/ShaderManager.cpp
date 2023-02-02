#include "ShaderManager.h"

Ark::ShaderManager::ShaderManager() {

}

bool Ark::ShaderManager::SetShaderPath(std::wstring shaderPath)
{
    m_shaderFolder = shaderPath.c_str();
       
    //TO DO: Check folder contains a pixel and vertex shader.

    return true;
}

bool Ark::ShaderManager::CompileVertexShader(std::wstring shaderFileName, Microsoft::WRL::ComPtr<ID3D11Device> &d3dDevice, std::string entryPoint)
{
    UINT shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    shaderFlags |= D3DCOMPILE_DEBUG;
#endif

    //Path Creation
    std::wstring fullShaderPath = m_shaderFolder + shaderFileName;

    //Blobs
    Microsoft::WRL::ComPtr <ID3DBlob> errorBlob = nullptr;
    Microsoft::WRL::ComPtr<ID3DBlob> vtxShaderBlob = nullptr;

    HRESULT compileResult = D3DCompileFromFile(fullShaderPath.c_str(), nullptr, nullptr, entryPoint.c_str(), "vs_5_0", shaderFlags, 0, &vtxShaderBlob, &errorBlob);

    if (FAILED(compileResult)) {
        MessageBoxA(NULL, "Vertex Shader Compilation Error", "Shader Error", MB_OK);
        return false;
    }

    Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;

    HRESULT createShaderResult = d3dDevice->CreateVertexShader(vtxShaderBlob->GetBufferPointer(), vtxShaderBlob->GetBufferSize(), nullptr, &vertexShader);

    if (FAILED(createShaderResult)) {
        MessageBoxA(NULL, "Vertex Shader Creation Error", "Shader Error", MB_OK);
        return false;
    }

    m_vertexShaders.push_back(vertexShader);    

    return true;
}

bool Ark::ShaderManager::CompilePixelShader(std::wstring shaderFileName, Microsoft::WRL::ComPtr<ID3D11Device> &d3dDevice, std::string entryPoint)
{
    UINT shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    shaderFlags |= D3DCOMPILE_DEBUG;
#endif

    //Path Creation
    std::wstring fullShaderPath = m_shaderFolder + shaderFileName;

    //Blobs
    Microsoft::WRL::ComPtr <ID3DBlob> errorBlob = nullptr;
    Microsoft::WRL::ComPtr<ID3DBlob> pxlShaderBlob = nullptr;

    HRESULT compileResult = D3DCompileFromFile(fullShaderPath.c_str(), nullptr, nullptr, entryPoint.c_str(), "ps_5_0", shaderFlags, 0, &pxlShaderBlob, &errorBlob);

    if (FAILED(compileResult)) {
        MessageBoxA(NULL, "Pixel Shader Compilation Error", "Shader Error", MB_OK);
        return false;
    }

    Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;

    HRESULT createShaderResult = d3dDevice->CreatePixelShader(pxlShaderBlob->GetBufferPointer(), pxlShaderBlob->GetBufferSize(), nullptr, &pixelShader);

    if (FAILED(createShaderResult)) {
        MessageBoxA(NULL, "Pixel Shader Creation Error", "Shader Error", MB_OK);
        return false;
    }

    m_pixelShaders.push_back(pixelShader);

    return true;
}
