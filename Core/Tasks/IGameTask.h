#pragma once
namespace engine
{
//=============================================================================
// INTERFACE IGameTask
//=============================================================================
// An IGameTask is executed as part of the game loop by the GameEngine. It is
// initialized once, then updated every frame, then cleanuped.
class IGameTask
{
public:
	virtual ~IGameTask() {}
public:
	// called when the task is added to the game loop
	virtual void init()  = 0;

	// called when the task is removed from the game loop
	virtual void cleanup() = 0;

	// called each frame
	virtual void update() = 0;
};
} // namespace engine
