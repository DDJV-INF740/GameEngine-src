//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Precompiled.h"
#include "GameTimer.h"
#include <windows.h>

//=============================================================================
// CLASS GameTimer
//=============================================================================
//------------------------------------------------------------------------------
//
static GameTimer::TimeStamp GetTimeStamp()
{
	LARGE_INTEGER tick;
	QueryPerformanceCounter(&tick);
	return tick.QuadPart;
}

//------------------------------------------------------------------------------
//
static double GetElapsedTime(GameTimer::TimeStamp startTime, GameTimer::TimeStamp endTime)
{
	static LARGE_INTEGER freq = {0};
	if (!freq.QuadPart) 
		QueryPerformanceFrequency(&freq);

	GameTimer::TimeStamp diff = endTime - startTime;

	return double(diff)/freq.QuadPart;
}

//------------------------------------------------------------------------------
//
void GameTimer::reset(float aRate)
{
	_accTime = 0;
	_startTime = GetTimeStamp();
	_rate = 1.0f;
}

//------------------------------------------------------------------------------
//
void GameTimer::setRate(float aRate)
{
	TimeStamp nowTime = GetTimeStamp();

	_accTime += GetElapsedTime(_startTime, nowTime) * _rate;
	_startTime = nowTime;
	_rate = aRate;
}

//------------------------------------------------------------------------------
//
double GameTimer::now()
{
	TimeStamp nowTime = GetTimeStamp();
	return _accTime + GetElapsedTime(_startTime, nowTime) * _rate;
}
