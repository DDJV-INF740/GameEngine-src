#include "Precompiled.h"
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "RenderViewComponent.h"
#include "Core/Game/Game.h"
#include "Core/GameManagers/IGameRendering.h"
#include "Core/GameObjects/IGameObject.h"
#include "Core/Components/IRenderInterface.h"
#include <d3d9.h>
#include <d3dx9math.h>
#include <PxPhysicsAPI.h>
using namespace physx;


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600



void RenderViewComponent::renderView()
{
	LPDIRECT3DDEVICE9 d3ddev = Game<IGameRendering>()->d3dDevice();

	d3ddev->BeginScene();
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	d3ddev->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

	{
		//-----------------------------------------------
		// Enable lights and materials
		d3ddev->SetRenderState(D3DRS_LIGHTING,true);

		D3DLIGHT9 light;
		ZeroMemory(&light,sizeof(light));
		light.Type = D3DLIGHT_DIRECTIONAL;
		light.Diffuse.r = 1.0f;
		light.Diffuse.g = 1.0f;
		light.Diffuse.b = 1.0f;
		light.Direction.x = 1.0f;
		light.Direction.y = -2.0f;
		light.Direction.z = 1.0f;
		light.Ambient.r = 0.2f;
		light.Ambient.g = 0.2f;
		light.Ambient.b = 0.2f;
		light.Range = 1000.0f;

		d3ddev->SetLight(0,&light);
		d3ddev->LightEnable(0,true);
	}


	D3DXMATRIX matView;    // the view transform matrix

	// look at the main player
	GameObjectRef target = gameObject();
	auto poseInterface = target->as<IPoseInterface>();
	PxTransform playerPos = poseInterface->pose();
// 	PxVec3 cameraPosition = getGlobalPose().p;
// 	D3DXMatrixLookAtLH(&matView,
// 		&D3DXVECTOR3 (cameraPosition.x, cameraPosition.y, cameraPosition.z),    // the camera position
// 		&D3DXVECTOR3 (playerPos.p.x, playerPos.p.y, playerPos.p.z),    // the look-at position
// 		&D3DXVECTOR3 (0.0f, 1.0f, 0.0f));    // the up direction

	physx::PxMat44 wViewMatrix(playerPos.getInverse());

	d3ddev->SetTransform(D3DTS_VIEW, (D3DMATRIX*)&wViewMatrix);    // set the view transform to matView

	D3DXMATRIX matProjection;     // the projection transform matrix

	D3DXMatrixPerspectiveFovLH(&matProjection,
		D3DXToRadian(60),    // the horizontal field of view
		(FLOAT)SCREEN_WIDTH / (FLOAT)SCREEN_HEIGHT, // aspect ratio
		1.0f,    // the near view-plane
		1000.0f);    // the far view-plane

	d3ddev->SetTransform(D3DTS_PROJECTION, &matProjection);    // set the projection

	const IGameRendering::RenderList& wRenderList = Game<IGameRendering>()->renderList();

	for (auto iter = wRenderList.begin(); iter != wRenderList.end(); ++iter)
	{
		(*iter)->render();
	}

	d3ddev->EndScene();

	d3ddev->Present(NULL, NULL, NULL, NULL);
}

GameObjectRef RenderViewComponent::gameObject()
{
	return _go.lock();
}

void RenderViewComponent::onAttached( const GameObjectRef &iGameObject )
{
	_go = iGameObject;
}

void RenderViewComponent::onDetached( const GameObjectRef &iGameObject )
{
	_go.reset();
}


//=============================================================================
// COMPONENT REGISTRATION
//=============================================================================
#include "Engine/Components/ComponentFactory.h"
IComponent::IdType RenderViewComponent::TypeId() { return "RenderViewComponent"; }
RegisterComponentType<RenderViewComponent> gRegisteredComponent;

