#pragma once

#include "Core/d3d/d3d9.forward.h"
#include "PxPhysicsAPI.h"

namespace engine {

class HeightMapRenderData
{
public:
	HeightMapRenderData()
		: _width(0)
		, _height(0)
		, _scale(1.0f, 1.0f, 1.0f)
		, _vbuffer(nullptr)
		, _ibuffer(nullptr)
	{}

public:
	int _width, _height;
	physx::PxVec3 _scale;
	LPDIRECT3DVERTEXBUFFER9 _vbuffer;
	LPDIRECT3DINDEXBUFFER9 _ibuffer;
};
} // namespace engine