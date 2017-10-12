#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponent.h"
#include "Core/Components/IRenderInterface.h"
#include "Core/Rendering/IRenderPrimitive.h"
#include "Engine/GameObjects/GameObjectComponent.h"
#include "Core/GameObjects/IGameObject.h"
#include <memory>

namespace engine {

//=============================================================================
// CLASS RenderComponent
//=============================================================================
class RenderComponent 
	: public GameObjectComponent<RenderComponent>
	, virtual public IRenderInterface
{
public:
	static constexpr IdType TypeId = "RenderComponent";
	static constexpr IdType Interfaces[] = {
		IRenderInterface::TypeId
	};

public: // IComponent
	virtual void onAttached(const GameObjectRef &iGameObject) override;
	virtual void onDetached(const GameObjectRef &iGameObject) override;

public: // IRenderInterface
	virtual void render() override;

public:
	void setRenderPrimitive(const IRenderPrimitiveRef &iRenderPrimitive);

private:
	IRenderPrimitiveRef _renderPrimitive;
	GameObjectWeakRef _go;
};

} // namespace engine
