#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/GameObjects/GameObjectFactory.h"
#include "Core/d3d/d3d9.forward.h"
#include <d3d9.h>

namespace engine {

struct SkyboxRenderData
{
public:
	d3d9::unique_ptr<IDirect3DVertexBuffer9> _vbuffer;
	d3d9::unique_ptr<IDirect3DIndexBuffer9> _ibuffer;
	d3d9::unique_ptr<IDirect3DTexture9> _texture;

	struct CUSTOMVERTEX
	{
		float X, Y, Z;
		float tu, tv;
		static const int FORMAT = D3DFVF_XYZ | D3DFVF_TEX1;
	};

public:
	int load(const TCHAR *iTexturePath, LPDIRECT3DDEVICE9 iD3dDev);
};
} // namespace engine
