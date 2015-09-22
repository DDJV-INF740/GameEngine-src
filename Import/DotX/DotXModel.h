#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Assets/Models/MeshModel.h"
#include "Core/d3d/d3d9.forward.h"

//=============================================================================
// CLASS DotXModel
//=============================================================================
class DotXModel: public MeshModel
{
public:
	DotXModel(LPDIRECT3DDEVICE9 aD3dDev, const char *aPathToDotX, const char *aPathToTextures);
	~DotXModel();

	virtual void render() const override;

private:
	class DotXModelImp;
	DotXModelImp *_imp;
};