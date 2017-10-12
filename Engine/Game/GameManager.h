#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Game/IManagerComponent.h"
#include "Core/Game/IManager.h"
#include "Core/Game/IGameEngine.h"
#include "Core/Components/ComponentBase.h"
#include <gsl/span>

namespace engine {

//=============================================================================
// CLASS GameManager
//=============================================================================
template<class TDerived>
class GameManager
	: virtual public IManagerComponent
	, virtual public IManager
{
public:
	virtual void onAttached(const GameEngineRef &iGameEngine) override {}
	virtual void onDetached(const GameEngineRef &iGameEngine) override {}

	virtual gsl::span<IdType> interfaces() override
	{
		return TDerived::Interfaces;
	}
};
} // namespace engine
