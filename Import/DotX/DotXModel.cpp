//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "DotXModel.h"

#include "Core/Logging/Logger.h"

#include <d3d9.h>
#include <d3dx9mesh.h>
#include <cstdio>
#include <vector>

namespace engine {

//=============================================================================
// CLASS DotXModel::DotXModelImp
//=============================================================================
class DotXModel::DotXModelImp
{
public:
	LPDIRECT3DDEVICE9 _d3ddev;
	std::vector<D3DMATERIAL9> _meshMaterials;
	std::vector<d3d9::unique_ptr<IDirect3DTexture9>> _meshTextures;
	DWORD _materialCount;

public:
	DotXModelImp(DotXModel *iIntrf, LPDIRECT3DDEVICE9 aD3dDev, const char *aPathToDotX, const char *aPathToTextures)
		: _intrf(iIntrf)
		, _d3ddev(aD3dDev)
		, _materialCount(0)
	{
		LPD3DXBUFFER _materials;

		LPD3DXMESH d3dwMesh;
		HRESULT hr = D3DXLoadMeshFromXA( aPathToDotX, D3DXMESH_MANAGED, _d3ddev, NULL, &_materials, NULL, &_materialCount, &d3dwMesh); 
		_intrf->setMesh(d3d9::unique_ptr<ID3DXMesh>(d3dwMesh));

		D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)_materials->GetBufferPointer();

		_meshMaterials.resize(_materialCount);
		_meshTextures.resize(_materialCount);

		// load the associated materials
		for (int i = 0; i < (int)_materialCount; ++i)
		{
			// Copy the material
			_meshMaterials[i] = d3dxMaterials[i].MatD3D;

			// Set the ambient color for the material (D3DX does not do this)
			_meshMaterials[i].Ambient = _meshMaterials[i].Diffuse;
     
			// Create the texture if it exists - it may not
			_meshTextures[i].reset();
			if (d3dxMaterials[i].pTextureFilename)
			{
				char path[1024];
				sprintf_s(path, sizeof(path), "%s%s", aPathToTextures, d3dxMaterials[i].pTextureFilename);
				LPDIRECT3DTEXTURE9 texture;
				D3DXCreateTextureFromFileA(_d3ddev, path, &texture);
				_meshTextures[i] = d3d9::unique_ptr<IDirect3DTexture9>(texture);
				LOG_INFO("loaded %s\n", path);
			}
		}
	}

	//-------------------------------------------------------------------------
	//
	void render()
	{
		D3DMATERIAL9 prevMaterial;
		_d3ddev->GetMaterial(&prevMaterial);

		for (int i = 0; i < (int)_materialCount; ++i)
		{
		   // Set the material and texture for this subset
		  _d3ddev->SetMaterial(&_meshMaterials[i]);
		  _d3ddev->SetTexture(0, _meshTextures[i].get());
        
		  // Draw the mesh subset
		  _intrf->mesh()->DrawSubset( i );
		}

		_d3ddev->GetMaterial(&prevMaterial);
		_d3ddev->SetTexture(0, 0);
	}

private:
	DotXModel *_intrf;
};

//=============================================================================
// CLASS DotXModel
//=============================================================================
DotXModel::DotXModel(LPDIRECT3DDEVICE9 aD3dDev, const char *aPathToDotX, const char *aPathToTextures)
	: _imp(new DotXModelImp(this, aD3dDev, aPathToDotX, aPathToTextures))
{}

//-----------------------------------------------------------------------------
//
DotXModel::~DotXModel()
{
	delete _imp;
}

//-----------------------------------------------------------------------------
//
void DotXModel::render() const
{
	_imp->render();
}
} // namespace engine
