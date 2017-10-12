#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponent.h"
#include "Core/GameManagers/IRenderManager.h"
#include "Engine/Game/GameManager.h"

namespace engine {

//=============================================================================
// CLASS RenderManager
//=============================================================================
class RenderManager
	: public GameManager<RenderManager>
	, public IRenderManager
{
public:
	static constexpr IdType TypeId = "RenderManager";
	static constexpr IdType Interfaces[] = {
		IRenderManager::TypeId
	};

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
	d3d9::unique_ptr<IDirect3D9> _d3d;
	d3d9::unique_ptr<IDirect3DDevice9> _d3ddev;
	RenderList _renderList;
};
} // namespace engine
