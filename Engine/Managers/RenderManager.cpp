#include "Precompiled.h"
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "RenderManager.h"
 #include <algorithm>
#include "Core/GameManagers/IWindowManager.h"

// include the Direct3D Library files
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

namespace engine {

//=============================================================================
// CLASS RenderManager
//=============================================================================

//-----------------------------------------------------------------------------
//
void RenderManager::removeFromRenderList( IRenderInterface *primitive )
{
	auto wFound = std::find(_renderList.begin(), _renderList.end(), primitive);
	if (wFound != _renderList.end())
	{
		_renderList.erase(wFound);
	}
}

//-----------------------------------------------------------------------------
//
void RenderManager::insertInRenderList( IRenderInterface *primitive )
{
	_renderList.emplace_back(primitive);
}

//-----------------------------------------------------------------------------
//
const RenderManager::RenderList& RenderManager::renderList()
{
	return _renderList;
}

//-----------------------------------------------------------------------------
//
LPDIRECT3DDEVICE9 RenderManager::d3dDevice()
{
	return _d3ddev.get();
}

//-----------------------------------------------------------------------------
//
IDirect3D9* RenderManager::d3d()
{
	return _d3d.get();
}

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
} // namespace engine

#include "d3d9.h"

namespace engine {


void RenderManager::onDetached( const GameEngineRef &iGameEngine )
{
	_d3ddev.reset();
	_d3d.reset();
}

void RenderManager::onAttached( const GameEngineRef &iGameEngine )
{
	auto wGameWindow = iGameEngine->as<IWindowManager>();
	ASSERT(wGameWindow != nullptr); // The engine must have a window before the render manager is initialized
	HWND hWnd = wGameWindow->window();

	_d3d = d3d9::unique_ptr<IDirect3D9>(Direct3DCreate9(D3D_SDK_VERSION));

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;


	IDirect3DDevice9 *d3ddev;
	// create a device class using this information and the info from the d3dpp stuct
	_d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	_d3ddev = d3d9::unique_ptr<IDirect3DDevice9>(d3ddev);

	_d3ddev->SetRenderState(D3DRS_LIGHTING, FALSE);    // turn off the 3D lighting}
}
} // namespace engine

