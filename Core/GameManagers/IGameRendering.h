#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Game/IGameInterface.h"
#include "Core/d3d/d3d9.forward.h"
#include <vector>

//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
class IGameObject;
class IRenderInterface;

//=============================================================================
// INTERFACE IGameRendering
//=============================================================================
class IGameRendering: virtual public IGameInterface
{
public:
	static IdType TypeId();
	typedef std::vector<IRenderInterface*> RenderList;
public:

	virtual IDirect3D9* d3d() = 0;
	virtual LPDIRECT3DDEVICE9 d3dDevice() = 0;

	virtual void removeFromRenderList(IRenderInterface *primitive) = 0;
	virtual void insertInRenderList(IRenderInterface *primitive) = 0;
	virtual const RenderList& renderList() = 0;
};