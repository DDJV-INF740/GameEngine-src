#include "Precompiled.h"
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "RenderManager.h"
 #include <algorithm>
#include "Core/GameManagers/IGameWindow.h"

// include the Direct3D Library files
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")


//=============================================================================
// CLASS RenderManager
//=============================================================================
//-----------------------------------------------------------------------------
//
IComponent::IdType RenderManager::TypeId() { return "RenderManager"; }

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
	_renderList.push_back(primitive);
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
	return _d3ddev;
}

//-----------------------------------------------------------------------------
//
IDirect3D9* RenderManager::d3d()
{
	return _d3d;
}

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#include "d3d9.h"



void RenderManager::onDetached( const GameEngineRef &iGameEngine )
{
	if (_d3ddev != nullptr)
	{
		_d3ddev->Release();    // close and release the 3D device
		_d3ddev = nullptr;
	}

	if (_d3d != nullptr)
	{
		_d3d->Release();    // close and release Direct3D
		_d3d = nullptr;
	}
}

void RenderManager::onAttached( const GameEngineRef &iGameEngine )
{
	auto wGameWindow = iGameEngine->as<IGameWindow>();
	ASSERT(wGameWindow != nullptr); // The engine must have a window before the render manager is initialized
	HWND hWnd = wGameWindow->window();

	_d3d = Direct3DCreate9(D3D_SDK_VERSION);

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


	// create a device class using this information and the info from the d3dpp stuct
	_d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&_d3ddev);


	_d3ddev->SetRenderState(D3DRS_LIGHTING, FALSE);    // turn off the 3D lighting}
}

#include "Engine/Managers/GameManagerFactory.h"
RegisterGameManagerType<RenderManager> gRenderManagerRegistration;

