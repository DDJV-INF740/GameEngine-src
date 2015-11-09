#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Game/IManager.h"
#include "Core/d3d/d3d9.forward.h"
#include <vector>

namespace engine
{

//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
class IGameObject;
class IRenderInterface;

//=============================================================================
// INTERFACE IRenderManager
//=============================================================================
class IRenderManager: virtual public IManager
{
public:
	static IdType TypeId();
	using RenderList = std::vector<IRenderInterface*>;
public:

	virtual IDirect3D9* d3d() = 0;
	virtual LPDIRECT3DDEVICE9 d3dDevice() = 0;

	virtual void removeFromRenderList(IRenderInterface *primitive) = 0;
	virtual void insertInRenderList(IRenderInterface *primitive) = 0;
	virtual const RenderList& renderList() = 0;
};
} // namespace engine
