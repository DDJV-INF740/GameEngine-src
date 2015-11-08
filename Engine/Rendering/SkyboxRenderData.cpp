#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Precompiled.h"
#include "SkyboxRenderData.h"
#include <d3dx9tex.h>

namespace engine {

//=============================================================================
// GLOBALS AND CONSTANTS
//=============================================================================

//-----------------------------------------------------------------------------
// create the vertices using the CUSTOMVERTEX struct
static const SkyboxRenderData::CUSTOMVERTEX vertices[] = {
	{ -1.0f,  1.0f, -1.0f, 0.25f, 0.34f},  // 0
	{  1.0f,  1.0f, -1.0f, 0.50f, 0.34f},  // 1
	{  1.0f, -1.0f, -1.0f, 0.50f, 0.66f},  // 2
	{ -1.0f, -1.0f, -1.0f, 0.25f, 0.66f},  // 3

	{  1.0f,  1.0f,  1.0f, 0.75f, 0.34f},  // 4
	{  1.0f, -1.0f,  1.0f, 0.75f, 0.66f},  // 5

	{ -1.0f,  1.0f,  1.0f, 0.25f, 0.0000f},// 6
	{  1.0f,  1.0f,  1.0f, 0.50f, 0.0000f},// 7

	{ -1.0f,  1.0f,  1.0f, 1.00f, 0.34f},  // 8
	{ -1.0f, -1.0f,  1.0f, 1.00f, 0.66f},  // 9

	{ -1.0f,  1.0f,  1.0f, 0.00f, 0.34f},  // 10
	{ -1.0f, -1.0f,  1.0f, 0.00f, 0.66f},  // 11

	{  1.0f, -1.0f,  1.0f, 0.50f, 1.0000f},// 12
	{ -1.0f, -1.0f,  1.0f, 0.25f, 1.0000f} // 13
};

//-----------------------------------------------------------------------------
//
static const short indices[] = {
	1, 0, 2, 3, // Front
	4, 1, 5, 2, // Right
	7, 6, 1, 0, // Top
	8, 4, 9, 5, // Back

	0, 10, 3, 11, // Left
	2, 3, 12, 13// Bottom
};

//-----------------------------------------------------------------------------
//
SkyboxRenderData::SkyboxRenderData() 
	: _vbuffer(nullptr)
	, _ibuffer(nullptr)
	, _texture(nullptr)
{}

//-----------------------------------------------------------------------------
//
int SkyboxRenderData::load( const TCHAR *iTexturePath, LPDIRECT3DDEVICE9 iD3dDev )
{
	::D3DXCreateTextureFromFile(iD3dDev, iTexturePath, &_texture);
	_tprintf("loaded %TS\n", iTexturePath);

	// create a vertex buffer interface called _vbuffer
	iD3dDev->CreateVertexBuffer(sizeof(vertices), 0, CUSTOMVERTEX::FORMAT, D3DPOOL_MANAGED, &_vbuffer, NULL);
	VOID* pVoid;    // a void pointer

	// lock _vbuffer and load the vertices into it
	_vbuffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, vertices, sizeof(vertices));
	_vbuffer->Unlock();

	iD3dDev->CreateIndexBuffer(sizeof(indices), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &_ibuffer, NULL);

	_ibuffer->Lock(0, sizeof(indices), &pVoid, NULL);
	memcpy(pVoid, indices, sizeof(indices));
	_ibuffer->Unlock();

	return 0;
}

//-----------------------------------------------------------------------------
//
SkyboxRenderData::~SkyboxRenderData()
{
	if (_texture)
	{
		_texture->Release();
		_texture = nullptr;
	}

	if (_vbuffer)
	{
		_vbuffer->Release();
		_vbuffer = nullptr;
	}

	if (_ibuffer)
	{
		_ibuffer->Release();
		_ibuffer = nullptr;
	}
}
} // namespace engine
