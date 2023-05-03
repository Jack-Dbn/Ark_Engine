#pragma once
#include <Windows.h>
#include <string>
#include <wrl.h>
#include <d3d11.h>
#include <d3d11_2.h>
#include "../Math.h"

namespace Ark {
	class Model
	{
	public:
		//0 is the default shader.
		Model(unsigned int vtxShader = 0);
		
		//Create mesh from manually defined meshes in Shapes.h
		bool SetMeshEx(
			void* vtxArray, 
			unsigned int vtxArraySize, 
			unsigned int* idxArray, 
			unsigned int idxArraySize, 
			Microsoft::WRL::ComPtr<ID3D11Device> &d3dDevice);

		//Create mesh from .obj file.
		bool SetMeshFromFile(std::string filePath, Microsoft::WRL::ComPtr<ID3D11Device>& d3dDevice, bool CwWindingDir = false, bool LH_Convert = true);

		ID3D11Buffer** GetVtxBufferAddr();
		ID3D11Buffer* GetIdxBuffer();

		unsigned int GetIdxCount();
		unsigned int GetVtxShaderId();

		//Flag to ensure entity cannot be rendered without being in a vertex buffer.
		bool m_RenderReady;

		Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;

		Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;
		unsigned int m_indexCount;

	private:
		//Static methods to create vertex and index buffer objects.
		static bool CreateVtxBuffer(
			Microsoft::WRL::ComPtr<ID3D11Device>& d3dDevice, 
			void* vtxArray, 
			unsigned int vtxArraySize, 
			Microsoft::WRL::ComPtr<ID3D11Buffer> &tgtBuffer);

		static bool CreateIdxBuffer(
			Microsoft::WRL::ComPtr<ID3D11Device>& d3dDevice, 
			unsigned int* idxArray, 
			unsigned int idxArraySize, 
			Microsoft::WRL::ComPtr<ID3D11Buffer> &tgtBuffer);

		//Index of vertex shader to use on this model.
		unsigned int m_vtxShaderPos;		
	};
}

