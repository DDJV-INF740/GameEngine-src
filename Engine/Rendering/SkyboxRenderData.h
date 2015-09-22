#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/GameObjects/GameObjectFactory.h"
#include "Core/d3d/d3d9.forward.h"
#include <d3d9.h>

struct SkyboxRenderData
{
public:
	LPDIRECT3DVERTEXBUFFER9 _vbuffer;
	LPDIRECT3DINDEXBUFFER9 _ibuffer;
	LPDIRECT3DTEXTURE9 _texture;

	struct CUSTOMVERTEX
	{
		float X, Y, Z;
		float tu, tv;
		static const int FORMAT = D3DFVF_XYZ | D3DFVF_TEX1;
	};

public:
	SkyboxRenderData();
	~SkyboxRenderData();

	int load(const TCHAR *iTexturePath, LPDIRECT3DDEVICE9 iD3dDev);
};
