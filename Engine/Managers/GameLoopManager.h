#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponent.h"
#include "Core/GameManagers/IGameLoop.h"
#include "Engine/Game/GameComponent.h"

//=============================================================================
// CLASS GameLoopManager
//=============================================================================
class GameLoopManager
	: public GameComponent<GameLoopManager>
	, public IGameLoop
{
public:
	static IComponent::IdType TypeId();
	static IComponentInterface::IdType* Interfaces()
	{
		static IComponentInterface::IdType sInterfaces[] = {
			IGameLoop::TypeId(),
			0
		};

		return sInterfaces;
	}

public: // IComponent
	virtual void onAttached(const GameEngineRef &iGameEngine) override {}
	virtual void onDetached(const GameEngineRef &iGameEngine) override {}

public: // IGameLoop
	virtual bool exitRequested() override;
	virtual void requestExit(bool iRequest) override;

public:
	GameLoopManager()
		: _exitRequested(false)
	{}

private:
	bool _exitRequested;
};