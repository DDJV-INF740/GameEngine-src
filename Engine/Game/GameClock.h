#pragma once

#include <chrono>
#include <Core/Game/GameClockBase.h>

namespace engine {

//=============================================================================
// CLASS GameClock
//=============================================================================
class GameClock : public GameClockBase
{
public:
	using native_time_point = std::chrono::high_resolution_clock::time_point;

	static native_time_point native_now() noexcept
	{
		return std::chrono::high_resolution_clock::now();
	}

public:
	time_point now() noexcept;

public:
	void reset(float aRate = 1.0f);
	void setRate(float aRate);
	float rate() { return _rate; }

private:
	native_time_point _startTime = GameClock::native_now();
	duration _accTime = duration(0);
	float _rate = 1.0f;
};

} // namespace engine
