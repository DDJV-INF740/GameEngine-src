#pragma once
//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
#include "Core/Components/IManagerObject.h"
#include "Core/Game/IManagerComponent.h"
#include "Core/Game/IManager.h"

namespace engine
{

//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
class IManager;
class IGameTask;

class IGameEngine;
using GameEngineRef = std::shared_ptr<IGameEngine>;
using GameEngineWeakRef = std::weak_ptr<IGameEngine>;

//=============================================================================
// CLASS IGameEngine
//=============================================================================
// The IGameEngine is the interface that a program must implement to use
// this game engine. Your main function should look like this:
// 
//	int main(int argc, const char *argv[])
//	{
//		IGameEngine::Instance()->init();
// 
//		while (IGameEngine::Instance()->run())
//		{
//		}
// 
//		IGameEngine::Instance()->cleanup();
//		return 0;
//	}
//
// And somewhere, you should implement the Instance() method to return
// your implementation of the IGameEngine. For example:
//
//	class DemoGame: public GameEngine
//	{
//		...
//	}
//
//	GameEngineRef IGameEngine::Instance()
//	{
//		static GameEngineRef sGame = std::make_shared<DemoGame>();
//		return sGame;
//	}
//
// In this example, we use the GameEngine base implementation.
//
// The IGameEngine supports managers as components. In other words, you
// may enable or disable managers at runtime by adding or removing 
// components to the game engine.  Components can be retrieved using
// IGameEngine::Instance()->as<IManagerType>() or more concisely
// by using Game<IManagerType>().
//
class IGameEngine : virtual public IManagerObject
{
public:
	// Global instance of the IGameEngine - must be implemented by the game
	static GameEngineRef& Instance();

public:
	virtual ~IGameEngine() = default;

public:
	// called when the game is being initialized
	virtual bool init()  = 0;

	// called continuously to tick the game and to execute all registered tasks
	virtual bool run()  = 0;

	// called when the game is about to exit
	virtual bool cleanup()  = 0;

	// adds a task which will be executed during the run phase
	virtual IGameTask* addTask(std::unique_ptr<IGameTask> iTask, int iPriority) = 0;

	template<class T>
	IGameTask* addTask(int iPriority)
	{
		return addTask(std::make_unique<T>(), iPriority);
	}

	// removes a task so it is no longer executed during the run phase
	virtual std::unique_ptr<IGameTask> removeTask(IGameTask *iTask) = 0;

	// changes the priority of a scheduled task
	virtual void setTaskPriority(IGameTask *iTask, int iPriority) = 0;

	// returns the priority of a scheduled task
	virtual int getTaskPriority(IGameTask *iTask) = 0;

public: // INTERFACE IComponentObject
	// same as Instance(), required for IComponentObject interface
	virtual GameEngineRef ref() = 0;
};

} // namespace engine
