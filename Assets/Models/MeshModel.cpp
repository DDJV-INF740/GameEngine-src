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
ID3DXMesh* MeshModel::mesh() const
{
	return _d3dMesh.get();
}

//-----------------------------------------------------------------------------
//
MeshModel::MeshModel(LPD3DXMESH iMesh)
	: _d3dMesh(iMesh)
{}

//-----------------------------------------------------------------------------
//
void MeshModel::render() const 
{
	_d3dMesh->DrawSubset(0);
}

void MeshModel::setMesh( d3d9::unique_ptr<ID3DXMesh> iMesh )
{
	_d3dMesh = std::move(iMesh);
}
} // namespace engine
