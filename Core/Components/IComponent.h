#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponentInterface.h"
#include <memory>

namespace engine
{
	
//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
class IGameObject;
typedef std::shared_ptr<IGameObject> GameObjectRef;
typedef std::weak_ptr<IGameObject> GameObjectWeakRef;

//=============================================================================
// INTERFACE IComponent
//=============================================================================
class IComponent
{
public:
	virtual ~IComponent() {}

public:
	typedef const char* IdType;
	static IdType NullId;

public:
	virtual IComponentInterface::IdType* interfaces() = 0;
	virtual void onAttached(const GameObjectRef &iGameObject) = 0;
	virtual void onDetached(const GameObjectRef &iGameObject) = 0;
};

} // namespace engine
