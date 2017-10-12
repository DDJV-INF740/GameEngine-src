#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponentInterface.h"
#include "Core/Components/IdType.h"
#include <memory>
#include <gsl/span>

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
	virtual gsl::span<IdType> interfaces() = 0;
	virtual void onAttached(const GameObjectRef &iGameObject) = 0;
	virtual void onDetached(const GameObjectRef &iGameObject) = 0;
};

} // namespace engine
