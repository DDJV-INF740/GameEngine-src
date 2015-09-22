#pragma once

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Models/IModel.h"
#include "Core/d3d/d3d9.forward.h"

//=============================================================================
// CLASS MeshModel 
//=============================================================================
class MeshModel : public IModel
{
public:
	LPD3DXMESH mesh() const;
	void setMesh(LPD3DXMESH iMesh);

public:
	MeshModel(LPD3DXMESH iMesh);
	MeshModel();
	~MeshModel();

	virtual void render() const override;

private:
	LPD3DXMESH _d3dMesh;
};

