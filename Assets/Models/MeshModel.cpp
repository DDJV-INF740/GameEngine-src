#include "Precompiled.h"
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "MeshModel.h"
#include <d3dx9mesh.h>

namespace engine {

//=============================================================================
// CLASS MeshModel
//=============================================================================

//-----------------------------------------------------------------------------
//
LPD3DXMESH MeshModel::mesh() const
{
	return _d3dMesh;
}

//-----------------------------------------------------------------------------
//
MeshModel::MeshModel(LPD3DXMESH iMesh)
	: _d3dMesh(iMesh)
{}

//-----------------------------------------------------------------------------
//
MeshModel::MeshModel()
	: _d3dMesh(nullptr)
{}

//-----------------------------------------------------------------------------
//
MeshModel::~MeshModel()
{
	// cleanup render objects
	if (_d3dMesh)
	{
		_d3dMesh->Release();
		_d3dMesh = nullptr;
	}
}

//-----------------------------------------------------------------------------
//
void MeshModel::render() const 
{
	_d3dMesh->DrawSubset(0);
}

void MeshModel::setMesh( LPD3DXMESH iMesh )
{
	_d3dMesh = iMesh;
}
} // namespace engine
