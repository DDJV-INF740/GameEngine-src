#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponent.h"
#include "Core/Components/ComponentBase.h"

namespace engine {

//=============================================================================
// CLASS GameObjectComponent
//=============================================================================
template<class TDerived>
class GameObjectComponent: virtual public IComponent, virtual public IComponentInterface
{
public:
	virtual void onAttached(const GameObjectRef &iGameObject) override {}
	virtual void onDetached(const GameObjectRef &iGameObject) override {}

	virtual IComponentInterface::IdType* interfaces() override
	{
		return TDerived::Interfaces();
	}
};
} // namespace engine
