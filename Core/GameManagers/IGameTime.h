#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Game/IGameInterface.h"

//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================

//=============================================================================
// INTERFACE IGameTime
//=============================================================================
class IGameTime: virtual public IGameInterface
{
public:
	static IdType TypeId();

public:
	virtual double currentTime() = 0;
	virtual double lastFrameTime() = 0;
	virtual void setGameRate(float iRate) = 0;

	virtual void startFrame() = 0;
	virtual void startSession() = 0;
};