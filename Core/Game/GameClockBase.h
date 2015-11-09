#pragma once

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include <chrono>

namespace engine {

//=============================================================================
// CLASS GameGameClockBase
//=============================================================================
struct GameClockBase
{
	using duration = std::chrono::duration<double>;
	using rep = duration::rep;
	using period = duration::period;
	using time_point = std::chrono::time_point<GameClockBase>;
	static const bool is_steady = true;
};

} // namespace engine