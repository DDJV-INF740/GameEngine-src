#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponent.h"
#include "Core/GameManagers/IRenderManager.h"
#include "Engine/Game/GameComponent.h"

//=============================================================================
// CLASS RenderManager
//=============================================================================
class RenderManager
	: public GameComponent<RenderManager>
	, public IRenderManager
{
public:
	static IComponent::IdType TypeId();
	static IComponentInterface::IdType* Interfaces()
	{
		static IComponentInterface::IdType sInterfaces[] = {
			IRenderManager::TypeId(),
			0
		};

		return sInterfaces;
	}

public: // IComponent
	virtual void onAttached(const GameEngineRef &iGameEngine) override;
	virtual void onDetached(const GameEngineRef &iGameEngine) override;

public: // IRenderManager
	virtual IDirect3D9* d3d() override;
	virtual LPDIRECT3DDEVICE9 d3dDevice() override;

	virtual void removeFromRenderList(IRenderInterface *primitive);
	virtual void insertInRenderList(IRenderInterface *primitive);
	virtual const RenderList& renderList();

private:
	IDirect3D9 *_d3d;
	LPDIRECT3DDEVICE9 _d3ddev;
	RenderList _renderList;
};