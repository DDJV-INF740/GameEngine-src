#pragma once

namespace engine {

//=============================================================================
// CLASS GameTimer
//=============================================================================
class GameTimer
{
public:
	typedef long long TimeStamp;

	void reset(float aRate = 1.0f);
	void setRate(float aRate);
	float rate() { return _rate; }
	double now();

private:
	TimeStamp _startTime;
	double _accTime;
	float _rate;
};

} // namespace engine
