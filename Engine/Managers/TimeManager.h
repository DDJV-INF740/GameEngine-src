#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include <vector>
#include "Engine/Components/PlayerComponent.h"
#include "Engine/Game/GameComponent.h"
#include "Core/GameManagers/ITimeManager.h"
#include "Engine/Game/GameTimer.h"

//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
class IGameObject;

class IGameEngine;
typedef std::shared_ptr<IGameEngine> GameEngineRef;
typedef std::weak_ptr<IGameEngine> GameEngineWeakRef;

//=============================================================================
// CLASS TimeManager
//=============================================================================
class TimeManager
	: public GameComponent<TimeManager>
	, public ITimeManager
{
public:
	static IComponent::IdType TypeId();
	static IComponentInterface::IdType* Interfaces()
	{
		static IComponentInterface::IdType sInterfaces[] = {
			ITimeManager::TypeId(),
			0
		};

		return sInterfaces;
	}

public: // IComponent
	virtual void onAttached(const GameEngineRef &iGameEngine) override {}
	virtual void onDetached(const GameEngineRef &iGameEngine) override {}

public: // IPlayerManager
	virtual double currentTime();
	virtual double lastFrameTime();
	virtual void setGameRate(float iRate);

	virtual void startFrame();
	virtual void startSession();

	TimeManager();

private:
	double _lastFrameTime;
	double _currentTime;
	GameTimer _sessionTimer;
};
