//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "DotXModel.h"

#include <d3d9.h>
#include <d3dx9mesh.h>
#include <cstdio>

//=============================================================================
// CLASS DotXModel::DotXModelImp
//=============================================================================
class DotXModel::DotXModelImp
{
public:
	LPDIRECT3DDEVICE9 _d3ddev;
	D3DMATERIAL9 *_meshMaterials;
	LPDIRECT3DTEXTURE9 *_meshTextures;
	DWORD _materialCount;

public:
	DotXModelImp(DotXModel *iIntrf, LPDIRECT3DDEVICE9 aD3dDev, const char *aPathToDotX, const char *aPathToTextures)
		: _intrf(iIntrf)
		, _d3ddev(aD3dDev)
		, _meshMaterials(nullptr)
		, _meshTextures(nullptr)
		, _materialCount(0)
	{
		LPD3DXBUFFER _materials;

		LPD3DXMESH d3dwMesh;
		HRESULT hr = D3DXLoadMeshFromXA( aPathToDotX, D3DXMESH_MANAGED, _d3ddev, NULL, &_materials, NULL, &_materialCount, &d3dwMesh); 
		_intrf->setMesh(d3dwMesh);

		D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)_materials->GetBufferPointer();

		_meshMaterials = new D3DMATERIAL9[_materialCount];
		_meshTextures  = new LPDIRECT3DTEXTURE9[_materialCount];

		// load the associated materials
		for (int i = 0; i < (int)_materialCount; ++i)
		{
			// Copy the material
			_meshMaterials[i] = d3dxMaterials[i].MatD3D;

			// Set the ambient color for the material (D3DX does not do this)
			_meshMaterials[i].Ambient = _meshMaterials[i].Diffuse;
     
			// Create the texture if it exists - it may not
			_meshTextures[i] = NULL;
			if (d3dxMaterials[i].pTextureFilename)
			{
				char path[1024];
				sprintf_s(path, sizeof(path), "%s%s", aPathToTextures, d3dxMaterials[i].pTextureFilename);
				D3DXCreateTextureFromFileA(_d3ddev, path, &_meshTextures[i]);
				printf("loaded %s\n", path);
			}
		}
	}

	//-------------------------------------------------------------------------
	//
	~DotXModelImp()
	{
		if (_meshTextures)
		{
			for (int i = 0; i < (int)_materialCount; ++i)
			{
				if (_meshTextures[i])
					_meshTextures[i]->Release();
			}
			delete [] _meshTextures;
			_meshTextures = nullptr;
		}
		
		if (_meshMaterials)
		{
			delete [] _meshMaterials;
			_meshMaterials = nullptr;
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
		  _d3ddev->SetTexture(0, _meshTextures[i]);
        
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

