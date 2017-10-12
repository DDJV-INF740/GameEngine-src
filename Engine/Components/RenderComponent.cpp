#include "Precompiled.h"
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "RenderComponent.h"
#include "Core/Game/Game.h"
#include "Rendering/Camera.h"
#include "Components/ComponentFactory.h"
#include "Core/GameManagers/IRenderManager.h"
#include "Core/GameObjects/IGameObject.h"

namespace engine {

//=============================================================================
// CLASS RenderComponent
//=============================================================================

//-----------------------------------------------------------------------------
//
void RenderComponent::onDetached(const GameObjectRef &iGameObject)
{
	Game<IRenderManager>()->removeFromRenderList(this);
	_go.reset();
}

//-----------------------------------------------------------------------------
//
void RenderComponent::setRenderPrimitive( const IRenderPrimitiveRef &iRenderPrimitive )
{
	_renderPrimitive = iRenderPrimitive;
	Game<IRenderManager>()->insertInRenderList(this);
}

//-----------------------------------------------------------------------------
//
void RenderComponent::render()
{
	_renderPrimitive->render(_go.lock());
}


//-----------------------------------------------------------------------------
//
void RenderComponent::onAttached( const GameObjectRef &iGameObject )
{
	_go = iGameObject;
}
} // namespace engine

