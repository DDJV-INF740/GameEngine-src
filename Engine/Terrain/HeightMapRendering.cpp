#include "Precompiled.h"

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "HeightMapRendering.h"
#include <d3d9.h>
#include "Core/Game/Game.h"
#include "Core/GameManagers/IRenderManager.h"
#include "TerrainData.h"

using namespace physx;

//=============================================================================
// CLASS HeightMapRendering
//=============================================================================

HeightMapRendering::HeightMapRendering( HeightMapRenderData *iData ) : _data(iData)
{

}

void HeightMapRendering::render( const GameObjectRef &iGameObject )
{
	LPDIRECT3DDEVICE9 d3ddev = Game<IRenderManager>()->d3dDevice();

	// select which vertex format we are using
	d3ddev->SetFVF(TerrainData::CUSTOMVERTEX::FORMAT);

	// select the vertex buffer to display
	d3ddev->SetStreamSource(0, _data->_vbuffer, 0, sizeof(TerrainData::CUSTOMVERTEX));
	d3ddev->SetIndices(_data->_ibuffer);

	PxMat44 transfo = PxMat44::createIdentity();
	d3ddev->SetTransform(D3DTS_WORLD, (D3DMATRIX*)&transfo);

	// copy the vertex buffer to the back buffer
	for (int y = 0; y < _data->_height-1; ++y)
	{
		d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, _data->_width*_data->_height, y*_data->_width*2, 2*(_data->_width-1));
		//d3ddev->DrawIndexedPrimitive(D3DPT_LINESTRIP, 0, 0, width*height, y*width*2, 2*width-1);
	}
}

