#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponent.h"
#include "Core/GameManagers/IGameLoopManager.h"
#include "Engine/Game/GameComponent.h"
namespace engine {

//=============================================================================
// CLASS GameLoopManager
//=============================================================================
class GameLoopManager
	: public GameComponent<GameLoopManager>
	, public IGameLoopManager
{
public:
	static IComponent::IdType TypeId();
	static IComponentInterface::IdType* Interfaces()
	{
		static IComponentInterface::IdType sInterfaces[] = {
			IGameLoopManager::TypeId(),
			0
		};

		return sInterfaces;
	}

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
