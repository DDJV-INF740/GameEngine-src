//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Precompiled.h"
#include "GameClock.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

namespace engine {

//=============================================================================
// CLASS GameClock
//=============================================================================
//------------------------------------------------------------------------------
//
static GameClock::native_time_point GetTimeStamp()
{
	return high_resolution_clock::now();
}

//------------------------------------------------------------------------------
//
static GameClock::duration GetElapsedTime(GameClock::native_time_point startTime, GameClock::native_time_point endTime)
{
	return endTime - startTime;
}

//------------------------------------------------------------------------------
//
void GameClock::reset(float aRate)
{
	_accTime = 0ms;
	_startTime = GetTimeStamp();
	_rate = 1.0f;
}

//------------------------------------------------------------------------------
//
void GameClock::setRate(float aRate)
{
	native_time_point nowTime = GetTimeStamp();

	_accTime += GetElapsedTime(_startTime, nowTime) * _rate;
	_startTime = nowTime;
	_rate = aRate;
}

//------------------------------------------------------------------------------
//
GameClock::time_point GameClock::now() noexcept
{
	native_time_point nowTime = GetTimeStamp();
	return time_point(_accTime + GetElapsedTime(_startTime, nowTime) * _rate);
}
} // namespace engine
