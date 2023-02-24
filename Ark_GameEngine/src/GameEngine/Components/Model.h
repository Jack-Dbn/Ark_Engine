#pragma once
#include <Windows.h>
#include <string>
#include <wrl.h>
#include <d3d11.h>
#include <d3d11_2.h>
#include "..\Component.h"

namespace Ark {
	class Model : Component
	{
	public:
		Model(unsigned int vtxShader = 0);
				
		bool SetMeshEx(
			void* vtxArray, 
			unsigned int vtxArraySize, 
			unsigned int* idxArray, 
			unsigned int idxArraySize, 
			Microsoft::WRL::ComPtr<ID3D11Device> &d3dDevice);

		bool SetMeshFromFile(std::string filePath, Microsoft::WRL::ComPtr<ID3D11Device>& d3dDevice, bool CwWindingDir = false, bool LH_Convert = true);

		ID3D11Buffer** GetVtxBufferAddr();
		ID3D11Buffer* GetIdxBuffer();

		unsigned int GetIdxCount();
		unsigned int GetVtxShaderId();

		bool m_RenderReady;

		Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;

		Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;
		unsigned int m_indexCount;

	private:
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

		unsigned int m_vtxShaderPos;		
	};
}

