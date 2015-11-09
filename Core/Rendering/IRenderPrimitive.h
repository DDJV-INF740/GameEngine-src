#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include <memory>

namespace engine {

//=============================================================================
// FORWARD DEFINITIONS
//=============================================================================
class IRenderViewInterface;
class IGameObject;
using GameObjectRef = std::shared_ptr<IGameObject>;
using GameObjectWeakRef = std::weak_ptr<IGameObject>;

//=============================================================================
// CLASS RenderPrimitive
//=============================================================================
class IRenderPrimitive
{
public:
	virtual ~IRenderPrimitive() = default;

public:
	virtual void render(const GameObjectRef &iGameObject) = 0;
};

//=============================================================================
// TYPE DEFINITIONS
//=============================================================================
using IRenderPrimitiveRef = std::shared_ptr<IRenderPrimitive>;

} // namespace engine
