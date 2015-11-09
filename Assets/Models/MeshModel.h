#pragma once

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Models/IModel.h"
#include "Core/d3d/d3d9.forward.h"

namespace engine {

//=============================================================================
// CLASS MeshModel 
//=============================================================================
class MeshModel : public IModel
{
public:
	ID3DXMesh* mesh() const;
	void setMesh(d3d9::unique_ptr<ID3DXMesh> iMesh);

public:
	MeshModel(LPD3DXMESH iMesh);
	MeshModel() = default;

	virtual void render() const override;

private:
	d3d9::unique_ptr<ID3DXMesh> _d3dMesh;
};
} // namespace engine

