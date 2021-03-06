#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IRenderViewInterface.h"
#include "Core/d3d/d3d9.forward.h"
#include "Core/GameObjects/IGameObject.h"
#include "Engine/GameObjects/GameObjectComponent.h"

namespace engine{

//=============================================================================
// CLASS RenderViewComponent
//=============================================================================
class RenderViewComponent 
	: public GameObjectComponent<RenderViewComponent>
	, virtual public IRenderViewInterface
{
public:
	static constexpr IdType TypeId = "RenderViewComponent";
	static constexpr IdType Interfaces[] = {
		IRenderViewInterface::TypeId,
	};

public: // IComponent
	virtual void onAttached(const GameObjectRef &iGameObject) override;
	virtual void onDetached(const GameObjectRef &iGameObject) override;

public: // IRenderViewInterface
	virtual void renderView() override;

public:
	GameObjectRef gameObject();

private:
	GameObjectWeakRef _go;
};
} // namespace engine
