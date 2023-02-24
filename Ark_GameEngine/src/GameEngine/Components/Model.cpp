#include "Model.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "..\include\tiny_obj_loader.h"

Ark::Model::Model(unsigned int vtxShader)
{
    m_vtxShaderPos = vtxShader;
    m_RenderReady = false;

    m_indexCount = 0;
}

bool Ark::Model::SetMeshEx(
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

bool Ark::Model::SetMeshFromFile(std::string filePath, Microsoft::WRL::ComPtr<ID3D11Device>& d3dDevice, bool CwWindingDir, bool LH_Convert)
{
    tinyobj::attrib_t attributes;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warning;
    std::string error;

    bool ret = tinyobj::LoadObj(&attributes, &shapes, &materials, &warning, &error, filePath.c_str());

    if (!warning.empty()) {
        MessageBoxA(NULL, warning.c_str(), "Tiny Obj Loading Warning", MB_OK);
    }

    if (!error.empty() || !ret) {
        MessageBoxA(NULL, error.c_str(), "Tiny Obj Loading Error", MB_OK);
        return false;
    }

    std::vector<Ark::vertex> vertexVector;
    std::vector<unsigned int> indexVector;

    size_t shapeOffset = 0;
    //Loop through shapes
    for (size_t s = 0; s < shapes.size(); s++) {
                
        size_t indexOffset = 0;

        //Reserve sizes
        vertexVector.reserve(shapes[s].mesh.indices.size());
        indexVector.reserve(shapes[s].mesh.indices.size());

        //Loop over the faces
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {

            size_t faceVerticesSize = size_t(shapes[s].mesh.num_face_vertices[f]);

            std::vector<unsigned int> tempIndexVector;

            //Loop over each vertex in the face
            for (size_t v = 0; v < faceVerticesSize; v++) {

                tinyobj::index_t index = shapes[s].mesh.indices[indexOffset + v];

                Ark::vertex tempVertex;
                
                size_t vertexIndex = 3 * size_t(index.vertex_index);

                //Set position of vertex
                tempVertex.pos.x = attributes.vertices[vertexIndex + 0];
                tempVertex.pos.y = attributes.vertices[vertexIndex + 1];
                tempVertex.pos.z = attributes.vertices[vertexIndex + 2];

                //If normal data is available, add it to the vertex data.
                if (index.normal_index >= 0) {

                    size_t normalIndex = 3 * size_t(index.normal_index);

                    tempVertex.normal.x = attributes.normals[normalIndex + 0];
                    tempVertex.normal.y = attributes.normals[normalIndex + 1];
                    tempVertex.normal.z = attributes.normals[normalIndex + 2];
                }

                //If tex coord data is available, add it to the vertex data.
                if (index.texcoord_index >= 0) {

                    size_t texIndex = 2 * size_t(index.texcoord_index);

                    tempVertex.texCoord.x = attributes.texcoords[texIndex + 0];
                    tempVertex.texCoord.y = attributes.texcoords[texIndex + 1];
                }

                //Conversion to left hand coordinate system
                if (LH_Convert) {
                    tempVertex.pos.z = -1.0f * tempVertex.pos.z;

                    tempVertex.normal.z = -1.0f * tempVertex.normal.z;

                    tempVertex.texCoord.y = 1.0f - tempVertex.texCoord.y;
                }

                vertexVector.push_back(tempVertex);
                if (CwWindingDir) {
                    tempIndexVector.push_back((unsigned int)shapeOffset + indexOffset + v);
                }
                else {
                    indexVector.push_back((unsigned int)shapeOffset + indexOffset + v);
                }
                
            }

            if (CwWindingDir) {
                indexVector.push_back(tempIndexVector.front());
                tempIndexVector.erase(tempIndexVector.begin());
                for (int t = 1; t < shapes[s].mesh.num_face_vertices[f]; t++) {
                    indexVector.push_back(tempIndexVector.back());
                    tempIndexVector.pop_back();
                }
            }

            indexOffset += faceVerticesSize;
        }

        shapeOffset = indexVector.size();
    }


    bool res = CreateVtxBuffer(d3dDevice, &vertexVector[0], vertexVector.size(), m_vertexBuffer);
    res = res && CreateIdxBuffer(d3dDevice, &indexVector[0], indexVector.size(), m_indexBuffer);

    if (!res) {
        return false;
    }

    m_indexCount = indexVector.size();
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
