#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Game/IGameEngine.h"
#include "Core/Tasks/IGameTask.h"
#include "Engine/Components/ComponentObject.h"
#include "Engine/Managers/GameManagerFactory.h"
#include "Core/Components/IComponent.h"
#include <vector>
#include <map>

#pragma warning( disable : 4250 )

namespace engine {

class GameTasks
{
public:
	GameTasks() = default;
	~GameTasks();
	void init();
	void update();
	IGameTask* addTask(std::unique_ptr<IGameTask> iTask, int iPriority);
	std::unique_ptr<IGameTask>  removeTask(IGameTask *iTask);
	void reset();
	int getPriority(IGameTask *iTask);
	void setPriority(IGameTask *iTask, int iPriority);

private:
	std::map<int, std::vector<std::unique_ptr<IGameTask>>> _tasks;
};


//=============================================================================
// CLASS Game
//=============================================================================
class GameEngine 
	: virtual public IGameEngine
	, public ComponentObject<IGameEngine, IManagerComponent, IManager, GameManagerFactory>
{
public:
	virtual bool init() override;
	virtual bool run() override;
	virtual bool cleanup() override; 

	virtual IGameTask* addTask(std::unique_ptr<IGameTask> iTask, int iPriority) override;

	template<class T>
	IGameTask* addTask(int iPriority) 
	{
		return IGameEngine::addTask<T>(iPriority);
	}

	virtual std::unique_ptr<IGameTask> removeTask(IGameTask *iTask) override;
	virtual void setTaskPriority(IGameTask *iTask, int iPriority) override;
	virtual int getTaskPriority(IGameTask *iTask) override;

	//-------------------------------------------------------------------------
	//
	GameEngineRef ref() override
	{
		return Instance();
	}

	virtual ~GameEngine();


public:
	GameTasks _tasks;
};

} // namespace engine
