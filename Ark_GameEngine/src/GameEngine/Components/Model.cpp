#include "Model.h"

Ark::Model::Model(unsigned int vtxShader)
{
    m_vtxShaderPos = vtxShader;
    m_RenderReady = false;

    m_indexCount = 0;
}

bool Ark::Model::SetMeshManual(
    void* vtxArray,
    unsigned int vtxArraySize, 
    unsigned int* idxArray, 
    unsigned int idxArraySize, 
    Microsoft::WRL::ComPtr<ID3D11Device> &d3dDevice)
{
    bool res = CreateVtxBuffer(d3dDevice, vtxArray, vtxArraySize, m_vertexBuffer);
    res = res && CreateIdxBuffer(d3dDevice, idxArray, idxArraySize, m_indexBuffer);

    if(!res) {
        return false;
    }

    m_indexCount = idxArraySize;
    m_RenderReady = true;

    return true;
}

ID3D11Buffer** Ark::Model::GetVtxBufferAddr()
{
    return m_vertexBuffer.GetAddressOf();
}

ID3D11Buffer* Ark::Model::GetIdxBuffer()
{
    return m_indexBuffer.Get();
}

unsigned int Ark::Model::GetIdxCount()
{
    return m_indexCount;
}

unsigned int Ark::Model::GetVtxShaderId()
{
    return m_vtxShaderPos;
}

bool Ark::Model::CreateVtxBuffer(Microsoft::WRL::ComPtr<ID3D11Device>& d3dDevice, void* vtxArray, unsigned int vtxArraySize, Microsoft::WRL::ComPtr<ID3D11Buffer>& tgtBuffer)
{
    //Vertex Buffer Creation
    D3D11_BUFFER_DESC vtxBufferDesc = { 0 };
    vtxBufferDesc.ByteWidth = sizeof(Ark::vertex) * vtxArraySize;
    vtxBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vtxBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vtxBufferDesc.CPUAccessFlags = 0;
    vtxBufferDesc.MiscFlags = 0;
    vtxBufferDesc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA vtxBufferData;
    vtxBufferData.pSysMem = vtxArray;
    vtxBufferData.SysMemPitch = 0;
    vtxBufferData.SysMemSlicePitch = 0;

    HRESULT res = d3dDevice->CreateBuffer(&vtxBufferDesc, &vtxBufferData, &tgtBuffer);

    if (FAILED(res)) {
        return false;
    }

    return true;
}

bool Ark::Model::CreateIdxBuffer(Microsoft::WRL::ComPtr<ID3D11Device>& d3dDevice, unsigned int* idxArray, unsigned int idxArraySize, Microsoft::WRL::ComPtr<ID3D11Buffer> &tgtBuffer)
{
    //Index Buffer Creation
    D3D11_BUFFER_DESC idxBufferDesc;
    idxBufferDesc.ByteWidth = sizeof(unsigned int) * idxArraySize;
    idxBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    idxBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    idxBufferDesc.CPUAccessFlags = 0;
    idxBufferDesc.MiscFlags = 0;
    idxBufferDesc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA idxBufferData;
    idxBufferData.pSysMem = idxArray;
    idxBufferData.SysMemPitch = 0;
    idxBufferData.SysMemSlicePitch = 0;

    HRESULT res = d3dDevice->CreateBuffer(&idxBufferDesc, &idxBufferData, &tgtBuffer);

    if (FAILED(res)) {
        return false;
    }

    return true;
}
