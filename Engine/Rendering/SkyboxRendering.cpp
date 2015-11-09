#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Precompiled.h"
#include "SkyboxRendering.h"
#include "SkyboxRenderData.h"
#include "Core/Game/Game.h"
#include "Core/GameManagers/IRenderManager.h"
#include "Core/Components/IPoseInterface.h"

#include "PxPhysicsAPI.h"
using namespace physx;

namespace engine {

//-------------------------------------------------------------------------
//
SkyboxRendering::SkyboxRendering( const SkyboxRenderData &iData ) 
	: _data(iData)
{}

//-------------------------------------------------------------------------
//
void SkyboxRendering::render( const GameObjectRef &iGameObject )
{
	LPDIRECT3DDEVICE9 d3ddev = Game<IRenderManager>()->d3dDevice();
	// select which vertex format we are using
	d3ddev->SetFVF(SkyboxRenderData::CUSTOMVERTEX::FORMAT);

	// select the vertex buffer to display
	d3ddev->SetStreamSource(0, _data._vbuffer.get(), 0, sizeof(SkyboxRenderData::CUSTOMVERTEX));
	d3ddev->SetIndices(_data._ibuffer.get());
	d3ddev->SetTexture(0, _data._texture.get());

	PxTransform t = iGameObject->as<IPoseInterface>()->pose();

	PxMat44 transfo = PxMat44::createIdentity();
	transfo.scale(PxVec4(20, 20, 20, 1));
	transfo.setPosition(t.p);
	d3ddev->SetTransform(D3DTS_WORLD, (D3DMATRIX*)&transfo);

	d3ddev->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	d3ddev->SetRenderState(D3DRS_LIGHTING,false);
	// copy the vertex buffer to the back buffer
	for (int i = 0; i < 6; i++) 
	{
		d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 14, i*4, 2);
		//d3ddev->DrawIndexedPrimitive(D3DPT_LINESTRIP, 0, 0, 14, i*4, 3);
	}

	d3ddev->SetRenderState(D3DRS_LIGHTING,true);
	d3ddev->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	d3ddev->SetTexture(0, nullptr);
}
} // namespace engine
