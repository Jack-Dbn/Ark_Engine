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
		Model();

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;
	};
}

