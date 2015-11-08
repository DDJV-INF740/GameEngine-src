#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Game/IGameManager.h"
#include "Core/Game/IGameInterface.h"
#include "Core/Game/IGameEngine.h"
#include "Core/Components/ComponentBase.h"

namespace engine {

//=============================================================================
// CLASS GameComponent
//=============================================================================
template<class TDerived>
class GameComponent
	: virtual public IGameManager
	, virtual public IGameInterface
{
public:
	virtual void onAttached(const GameEngineRef &iGameEngine) override {}
	virtual void onDetached(const GameEngineRef &iGameEngine) override {}

	virtual IGameInterface::IdType* interfaces() override
	{
		return TDerived::Interfaces();
	}
};
} // namespace engine
