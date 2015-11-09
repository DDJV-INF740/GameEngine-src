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
using GameObjectRef = std::shared_ptr<IGameObject>;
using GameObjectWeakRef = std::weak_ptr<IGameObject>;

//=============================================================================
// INTERFACE IComponent
//=============================================================================
class IComponent
{
public:
	virtual ~IComponent() {}

public:
	using IdType = const char*;
	static IdType NullId;

public:
	virtual IComponentInterface::IdType* interfaces() = 0;
	virtual void onAttached(const GameObjectRef &iGameObject) = 0;
	virtual void onDetached(const GameObjectRef &iGameObject) = 0;
};

} // namespace engine
