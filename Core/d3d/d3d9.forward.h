#pragma once
#include <memory>

//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
typedef struct IDirect3DDevice9 *LPDIRECT3DDEVICE9, *PDIRECT3DDEVICE9;
typedef struct IDirect3DVertexBuffer9 *LPDIRECT3DVERTEXBUFFER9, *PDIRECT3DVERTEXBUFFER9;
typedef struct IDirect3DIndexBuffer9 *LPDIRECT3DINDEXBUFFER9, *PDIRECT3DINDEXBUFFER9;
typedef struct IDirect3DTexture9 *LPDIRECT3DTEXTURE9, *PDIRECT3DTEXTURE9;
typedef struct ID3DXMesh *LPD3DXMESH;
typedef struct HWND__ *HWND;
typedef struct IDirect3D9 IDirect3D9;

namespace d3d9 {
	// custom deleter for unique_ptr
	template<class _Ty>
	struct d3d9_deleter
	{
		void operator()(_Ty *_Ptr) const _NOEXCEPT
		{
			_Ptr->Release();
		}
	};

	template<class _Ty>
	using unique_ptr = std::unique_ptr<_Ty, d3d9_deleter<_Ty>>;
}
