#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include <vector>
#include "Engine/Components/PlayerComponent.h"
#include "Engine/Game/GameComponent.h"
#include "Core/GameManagers/ITimeManager.h"
#include "Engine/Game/GameClock.h"

namespace engine {

//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
class IGameObject;

class IGameEngine;
using GameEngineRef = std::shared_ptr<IGameEngine>;
using GameEngineWeakRef = std::weak_ptr<IGameEngine>;

//=============================================================================
// CLASS TimeManager
//=============================================================================
class TimeManager
	: public GameComponent<TimeManager>
	, public ITimeManager
{
public:
	using time_point = GameClock::time_point;

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
	virtual time_point currentTime() noexcept override;
	virtual time_point lastFrameTime() noexcept override;
	virtual void setGameRate(float iRate) override;

	virtual void startFrame() override;
	virtual void startSession() override;

	TimeManager();

private:
	time_point _lastFrameTime;
	time_point _currentTime;
	GameClock _sessionTimer;
};
} // namespace engine
