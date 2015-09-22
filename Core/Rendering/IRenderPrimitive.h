#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include <memory>

//=============================================================================
// FORWARD DEFINITIONS
//=============================================================================
class IRenderViewInterface;
class IGameObject;
typedef std::shared_ptr<IGameObject> GameObjectRef;
typedef std::weak_ptr<IGameObject> GameObjectWeakRef;

//=============================================================================
// CLASS RenderPrimitive
//=============================================================================
class IRenderPrimitive
{
public:
	virtual ~IRenderPrimitive() {}

public:
	virtual void render(const GameObjectRef &iGameObject) = 0;
};

//=============================================================================
// TYPE DEFINITION
//=============================================================================
typedef std::shared_ptr<IRenderPrimitive> IRenderPrimitiveRef;
