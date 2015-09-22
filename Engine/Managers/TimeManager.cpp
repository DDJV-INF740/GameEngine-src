#include "Precompiled.h"
#include "TimeManager.h"


double TimeManager::currentTime()
{
	return _currentTime;
}

double TimeManager::lastFrameTime()
{
	return _lastFrameTime;
}

void TimeManager::setGameRate( float iRate )
{
	_sessionTimer.setRate(1.0f);
}

TimeManager::TimeManager() 
	: _lastFrameTime(0)
	, _currentTime(0)
	, _sessionTimer()
{
	_sessionTimer.reset();
}

void TimeManager::startFrame()
{
	_lastFrameTime = _currentTime;
	_currentTime = _sessionTimer.now();
}

void TimeManager::startSession()
{
	_currentTime = 0; 
	_lastFrameTime = 0;
	_sessionTimer.reset();
	_sessionTimer.setRate(1.0f);
}

//=============================================================================
// COMPONENT REGISTRATION
//=============================================================================
#include "Engine/Managers/GameManagerFactory.h"
IComponent::IdType TimeManager::TypeId() { return "TimeManager"; }
static RegisterGameManagerType<TimeManager> gRegisteredComponent;


