#include "Precompiled.h"
#include "TimeManager.h"

namespace engine {


TimeManager::time_point TimeManager::currentTime() noexcept
{
	return _currentTime;
}

TimeManager::time_point TimeManager::lastFrameTime() noexcept
{
	return _lastFrameTime;
}

void TimeManager::setGameRate( float iRate )
{
	_sessionTimer.setRate(iRate);
}

TimeManager::TimeManager() 
	: _lastFrameTime()
	, _currentTime()
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
	_currentTime = TimeManager::time_point::min(); 
	_lastFrameTime = TimeManager::time_point::min();
	_sessionTimer.reset(1.0f);
}
} // namespace engine

