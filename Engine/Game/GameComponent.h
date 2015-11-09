#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Game/IManagerComponent.h"
#include "Core/Game/IManager.h"
#include "Core/Game/IGameEngine.h"
#include "Core/Components/ComponentBase.h"

namespace engine {

//=============================================================================
// CLASS GameComponent
//=============================================================================
template<class TDerived>
class GameComponent
	: virtual public IManagerComponent
	, virtual public IManager
{
public:
	virtual void onAttached(const GameEngineRef &iGameEngine) override {}
	virtual void onDetached(const GameEngineRef &iGameEngine) override {}

	virtual IManager::IdType* interfaces() override
	{
		return TDerived::Interfaces();
	}
};
} // namespace engine
