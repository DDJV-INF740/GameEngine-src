#include "Precompiled.h"

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/GameObjects/IGameObjectData.h"
#include "HeightMapData.h"
#include <PxPhysicsAPI.h>
#include <tchar.h>
#include <windows.h>
#include <d3d9.h>

//=============================================================================
// CLASS TerrainData
//=============================================================================
class TerrainData: public IGameObjectData
{
public:
	struct CUSTOMVERTEX {
		physx::PxVec3 p;
		physx::PxVec3 n;
		DWORD COLOR;
		static const int FORMAT = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE;
	};

public:
	HeightMapRenderData _renderData;

	physx::PxMaterial *_material;
	physx::PxHeightFieldSample *_heightMap;
	physx::PxHeightField *_heightField;

public:
	TerrainData();
	~TerrainData();

	//-------------------------------------------------------------------------
	//
	virtual TCHAR* heightMapFile() { return _T("assets/terrain64x64.bmp"); }
	physx::PxVec3 heightMapScale() { return physx::PxVec3(100, 10, 100); }

	//-------------------------------------------------------------------------
	//
	int load();
};
