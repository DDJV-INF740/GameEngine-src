#include "Precompiled.h"

#include "TerrainData.h"
#include "Import/Images/OLEImageImporter.h"
#include "Core/GameManagers/IRenderManager.h"
#include "Core/GameManagers/ISimulationManager.h"
#include "Core/Game/Game.h"
#include <d3d9.h>


using namespace physx;

namespace engine {


//-----------------------------------------------------------------------------
//
unsigned char LinearInterpolate(int val, int iMin, int iMax, int oMin, int oMax)
{
	return (val-iMin)*(oMax-oMin)/(iMax-iMin) + oMin;
}

//-----------------------------------------------------------------------------
//
unsigned int ColorForHeight(unsigned char height)
{
	int r, g, b;
	if (height > 235)
	{
		r = g = b = height;
	}
	else if (height > 200)
	{
		r = LinearInterpolate(height, 200, 235, 150, 235);
		g = 235;
		b = LinearInterpolate(height, 200, 235, 150, 235);
	}
	else if (height >  160)
	{
		r = 150;
		g = LinearInterpolate(height, 160, 200, 150, 235);
		b = 150;
	}
	else if (height > 80)
	{
		r = LinearInterpolate(height, 80, 160, 200, 150);
		g = LinearInterpolate(height, 80, 160, 200, 150);
		b = LinearInterpolate(height, 80, 160, 80, 150);
	}
	else
	{
		r = LinearInterpolate(height, 0, 80, 32, 200);
		g = LinearInterpolate(height, 0, 80, 32, 200);
		b = LinearInterpolate(height, 0, 80, 16, 80);
	}

	return D3DCOLOR_XRGB(r, g, b);
}

int TerrainData::load()
{
	static const TCHAR *kHeightPixMapFile = heightMapFile();
	_renderData._scale = heightMapScale();

	// Load the image file
	unsigned char *buffer;
	OLEImageImporter imgLoader(kHeightPixMapFile);
	imgLoader.getNativeSize(&_renderData._width, &_renderData._height);
	buffer = (unsigned char*)malloc(_renderData._width*_renderData._height);
	imgLoader.draw(buffer, OLEImageImporter::FORMAT_L8);
	_tprintf("loaded  %TS\n", kHeightPixMapFile);

	LPDIRECT3DDEVICE9 d3ddev = Game<IRenderManager>()->d3dDevice();
	int verticeCount = _renderData._width*_renderData._height;

	// create a vertex buffer interface called _vbuffer
	d3ddev->CreateVertexBuffer(verticeCount*sizeof(CUSTOMVERTEX), 0, CUSTOMVERTEX::FORMAT, D3DPOOL_MANAGED, &_renderData._vbuffer, NULL);
	CUSTOMVERTEX* pVoid;    // a void pointer

	_heightMap = new PxHeightFieldSample[_renderData._width*_renderData._height];

	// lock _vbuffer and load the vertices into it
	_renderData._vbuffer->Lock(0, 0, (void**)&pVoid, 0);
	for (int y = 0; y < _renderData._height; ++y)
	{
		for (int x = 0; x < _renderData._width; ++x)
		{
			pVoid[x+y*_renderData._width].p.x = (x-_renderData._width/2.0f)/(_renderData._width-1) * _renderData._scale.x;
			pVoid[x+y*_renderData._width].p.y = (buffer[x+y*_renderData._width]-255.0f/2)/255.0f * _renderData._scale.y;
			pVoid[x+y*_renderData._width].p.z = (y-_renderData._height/2.0f)/(_renderData._height-1) * _renderData._scale.z;
			pVoid[x+y*_renderData._width].COLOR = ColorForHeight(buffer[x+y*_renderData._width]);
		}
	}

	// compute normals
	for (int y = 0; y < _renderData._height; ++y)
	{
		for (int x = 0; x < _renderData._width; ++x)
		{
			PxVec3 vx;
			if (x > 0 && x < _renderData._width-1)
			{
				vx = pVoid[(x+1)+y*_renderData._width].p - pVoid[(x-1)+y*_renderData._width].p;
			}
			else if (x > 0)
			{
				vx = pVoid[(x)+y*_renderData._width].p-pVoid[(x-1)+y*_renderData._width].p;
			}
			else if (x < _renderData._width-1)
			{
				vx = pVoid[(x+1)+y*_renderData._width].p-pVoid[(x)+y*_renderData._width].p;
			}

			PxVec3 vy;
			if (y > 0 && y < _renderData._height-1)
			{
				vy = pVoid[x+(y+1)*_renderData._width].p - pVoid[x+(y-1)*_renderData._width].p;
			}
			else if (y > 0)
			{
				vy = pVoid[x+(y)*_renderData._width].p - pVoid[x+(y-1)*_renderData._width].p;
			}
			else if (y < _renderData._height-1)
			{
				vy = pVoid[x+(y+1)*_renderData._width].p - pVoid[x+(y)*_renderData._width].p;
			}

			pVoid[x+y*_renderData._width].n = vy.cross(vx).getNormalized();
		}
	}

	for (int y = 0; y < _renderData._height; ++y)
	{
		for (int x = 0; x < _renderData._width; ++x)
		{
			_heightMap[x*_renderData._height+y].height = PxI16(65535*pVoid[x+y*_renderData._width].p.y/_renderData._scale.y);
			_heightMap[x*_renderData._height+y].materialIndex0 = 0;
			_heightMap[x*_renderData._height+y].materialIndex1 = 0;
			_heightMap[x*_renderData._height+y].clearTessFlag();
		}
	}
	_renderData._vbuffer->Unlock();

	d3ddev->CreateIndexBuffer(2*_renderData._width*(_renderData._height-1)*sizeof(int), D3DUSAGE_WRITEONLY, D3DFMT_INDEX32, D3DPOOL_DEFAULT, &_renderData._ibuffer, NULL);

	int* pIdx;    // a void pointer
	_renderData._ibuffer->Lock(0, 0, (VOID**)&pIdx, NULL);
	int i = 0;
	for (int y = 0; y < _renderData._height-1; ++y)
	{
		for (int x = 0; x < _renderData._width; ++x)
		{
			pIdx[i++] = x+y*_renderData._width;
			pIdx[i++] = x+(y+1)*_renderData._width;
		}
	}
	_renderData._ibuffer->Unlock();

	PxPhysics &physics = Game<ISimulationManager>()->physics();

	_material = physics.createMaterial(0.5f, 0.5f, 0.1f);    //static friction, dynamic friction, restitution

	PxHeightFieldDesc heightMapDesc;
	heightMapDesc.format = PxHeightFieldFormat::eS16_TM;
	heightMapDesc.nbColumns = _renderData._width;
	heightMapDesc.nbRows = _renderData._height;
	heightMapDesc.samples.data = _heightMap;
	heightMapDesc.samples.stride = sizeof(PxHeightFieldSample);
	_heightField = physics.createHeightField(heightMapDesc);
	return 0;
}

TerrainData::TerrainData() : _renderData()
	, _material(nullptr)
	, _heightMap(nullptr)
	, _heightField(nullptr)
{

}

TerrainData::~TerrainData()
{
	if (_renderData._vbuffer)
	{
		_renderData._vbuffer->Release();
		_renderData._vbuffer = nullptr;
	}
	if (_renderData._ibuffer)
	{
		_renderData._ibuffer->Release();
		_renderData._ibuffer = nullptr;
	}

	if (_heightField)
	{
		_heightField->release();
		_heightField = nullptr;
	}

	if (_material)
	{
		_material->release();
		_material = nullptr;
	}

	if (_heightMap)
	{
		delete [] _heightMap;
	}
}
} // namespace engine
