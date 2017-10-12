#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponent.h"
#include "Core/Components/ComponentBase.h"
#include "Core/span.h"
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

	virtual span<IdType> interfaces() override
	{
		return TDerived::Interfaces;
	}
};
} // namespace engine
