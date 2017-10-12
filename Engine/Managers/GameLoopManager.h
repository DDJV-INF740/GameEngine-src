#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponent.h"
#include "Core/GameManagers/IGameLoopManager.h"
#include "Engine/Game/GameManager.h"
namespace engine {

//=============================================================================
// CLASS GameLoopManager
//=============================================================================
class GameLoopManager
	: public GameManager<GameLoopManager>
	, public IGameLoopManager
{
public:
	static constexpr IdType TypeId = "GameLoopManager";
	static constexpr IdType Interfaces[] = {
		IGameLoopManager::TypeId
	};

public: // IComponent
	virtual void onAttached(const GameEngineRef &iGameEngine) override {}
	virtual void onDetached(const GameEngineRef &iGameEngine) override {}

public: // IGameLoopManager
	virtual bool exitRequested() override;
	virtual void requestExit(bool iRequest) override;

public:
	GameLoopManager()
		: _exitRequested(false)
	{}

private:
	bool _exitRequested;
};
} // namespace engine
