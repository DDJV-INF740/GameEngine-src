#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Game/IManager.h"
#include "Core/Game/GameClockBase.h"
#include "Core/Components/IdType.h"

namespace engine {

//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================

//=============================================================================
// INTERFACE ITimeManager
//=============================================================================
class ITimeManager: virtual public IManager
{

public:
	using duration = GameClockBase::duration;
	using time_point = GameClockBase::time_point;

public:
	static constexpr IdType TypeId = "ITimeManager";

public:
	virtual time_point currentTime() = 0;
	virtual time_point lastFrameTime() = 0;
	virtual void setGameRate(float iRate) = 0;

	virtual void startFrame() = 0;
	virtual void startSession() = 0;
};
} // namespace engine
