#include "Precompiled.h"

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "ModelRendering.h"
#include "Core/GameObjects/IGameObject.h"
#include "Core/Models/IModel.h"
#include "Core/Components/IPoseInterface.h"
#include "Core/GameManagers/IRenderManager.h"
#include "Core/Components/IRenderViewInterface.h"
#include "Core/Game/Game.h"
#include <d3d9.h>

#include "PxPhysicsAPI.h"
using namespace physx;

//=============================================================================
// CLASS ModelRendering
//=============================================================================

//-------------------------------------------------------------------------
//
ModelRendering::ModelRendering(const IModel &iModel)
	: _model(iModel)
{}

//-------------------------------------------------------------------------
//
void ModelRendering::render(const GameObjectRef &iGameObject)
{
	LPDIRECT3DDEVICE9 wD3dDevice = Game<IRenderManager>()->d3dDevice();

	PxMat44 wMatrixTransfo(PxIdentity);
	IPoseInterfaceRef wGOPose = iGameObject->as<IPoseInterface>();
	if (wGOPose)
	{
		wMatrixTransfo = PxMat44(wGOPose->pose());
	}

	wD3dDevice->SetTransform(D3DTS_WORLD, (D3DMATRIX*)&wMatrixTransfo);
	_model.render();
}
