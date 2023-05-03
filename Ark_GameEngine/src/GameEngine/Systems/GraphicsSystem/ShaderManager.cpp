#include "ShaderManager.h"

Ark::ShaderManager::ShaderManager() {

}

bool Ark::ShaderManager::SetShaderPath(std::wstring shaderPath)
{
    m_shaderFolder = shaderPath.c_str();

    return true;
}

bool Ark::ShaderManager::CompileVertexShader(std::wstring shaderFileName, Microsoft::WRL::ComPtr<ID3D11Device>& d3dDevice, std::string entryPoint)
{
    UINT shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    shaderFlags |= D3DCOMPILE_DEBUG;
#endif

    //Path Creation
    std::wstring fullShaderPath = m_shaderFolder + shaderFileName;

    //Blobs
    Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;
    Microsoft::WRL::ComPtr<ID3DBlob> vtxShaderBlob = nullptr;

    //Compile
    HRESULT compileResult = D3DCompileFromFile(fullShaderPath.c_str(), nullptr, nullptr, entryPoint.c_str(), "vs_5_0", shaderFlags, 0, &vtxShaderBlob, &errorBlob);

    //Notify user when shaders have failed to compile.
    if (FAILED(compileResult)) {
        MessageBoxA(NULL, "Vertex Shader Compilation Error", "Shader Error", MB_OK);
        return false;
    }

    Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;

    //Create vertex shader object.
    HRESULT createShaderResult = d3dDevice->CreateVertexShader(vtxShaderBlob->GetBufferPointer(), vtxShaderBlob->GetBufferSize(), nullptr, &vertexShader);

    if (FAILED(createShaderResult)) {
        MessageBoxA(NULL, "Vertex Shader Creation Error", "Shader Error", MB_OK);
        return false;
    }

    //Add vertex shader object to vertex shader vector.
    m_vertexShaders.push_back(vertexShader);

    return this->CreateInputLayout(vtxShaderBlob, d3dDevice);
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
    Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;
    Microsoft::WRL::ComPtr<ID3DBlob> pxlShaderBlob = nullptr;

    //Compile
    HRESULT compileResult = D3DCompileFromFile(fullShaderPath.c_str(), nullptr, nullptr, entryPoint.c_str(), "ps_5_0", shaderFlags, 0, &pxlShaderBlob, &errorBlob);

    if (FAILED(compileResult)) {
        MessageBoxA(NULL, "Pixel Shader Compilation Error", "Shader Error", MB_OK);
        return false;
    }

    Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;

    //Create pixel shader object.
    HRESULT createShaderResult = d3dDevice->CreatePixelShader(pxlShaderBlob->GetBufferPointer(), pxlShaderBlob->GetBufferSize(), nullptr, &pixelShader);

    if (FAILED(createShaderResult)) {
        MessageBoxA(NULL, "Pixel Shader Creation Error", "Shader Error", MB_OK);
        return false;
    }

    //Add pixel shader object to pixel shader vector.
    m_pixelShaders.push_back(pixelShader);

    return true;
}

bool Ark::ShaderManager::CreateInputLayout(Microsoft::WRL::ComPtr<ID3DBlob> &vtxShaderBlob, Microsoft::WRL::ComPtr<ID3D11Device>& d3dDevice)
{
    Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;

    //Describe vertex format.
    const D3D11_INPUT_ELEMENT_DESC vertexLayoutDesc[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"NORMAL",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },//Offset 12 bytes, so its after position data.
        {"TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }//Offset 24 bytes, so its after position & normal data.
    };

    //Create the layout with the description.
    HRESULT res = d3dDevice->CreateInputLayout(
        vertexLayoutDesc,
        ARRAYSIZE(vertexLayoutDesc),
        vtxShaderBlob->GetBufferPointer(),
        vtxShaderBlob->GetBufferSize(),
        &inputLayout
        );

    //Add layout to vector.
    m_inputLayouts.push_back(inputLayout);

    return true;
}

ID3D11VertexShader* Ark::ShaderManager::GetVtxShader(unsigned int shaderPos)
{
    return m_vertexShaders[shaderPos].Get();
}

ID3D11PixelShader* Ark::ShaderManager::GetPxlShader(unsigned int shaderPos)
{
    return m_pixelShaders[shaderPos].Get();
}

ID3D11InputLayout* Ark::ShaderManager::GetInputLayout(unsigned int layoutPos)
{
    return m_inputLayouts[layoutPos].Get();
}
