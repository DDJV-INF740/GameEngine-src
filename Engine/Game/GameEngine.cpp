//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Precompiled.h"
#include "GameEngine.h"
#include "Core/Game/Game.h"
#include "Core/GameManagers/IGameLoopManager.h"
#include "Core/GameObjects/GameObjectFactory.h"
#include "Engine/Managers/GameManagerFactory.h"
#include "Engine/Components/ComponentFactory.h"
#include <algorithm>

namespace engine {

template<class T>
struct unique_ptr_equals_ptr_t
{
	T *_ptr;
	unique_ptr_equals_ptr_t(T *ptr) : _ptr(ptr) {}
	bool operator()(const std::unique_ptr<T> &rhs)
	{
		return rhs.get() == _ptr;
	}
};

template<class T>
unique_ptr_equals_ptr_t<T> unique_ptr_equals_ptr(T *ptr)
{
	return unique_ptr_equals_ptr_t<T>(ptr);
}

GameTasks::~GameTasks()
{

}

void GameTasks::init()
{
	for (auto taskGroupIter = _tasks.begin(); taskGroupIter != _tasks.end(); ++taskGroupIter)
	{
		for (auto taskIter = taskGroupIter->second.begin(); taskIter != taskGroupIter->second.end(); ++taskIter)
		{
			(*taskIter)->init();
		}
	}
}

void GameTasks::update()
{
	for (auto taskGroupIter = _tasks.begin(); taskGroupIter != _tasks.end(); ++taskGroupIter)
	{
		for (auto taskIter = taskGroupIter->second.begin(); taskIter != taskGroupIter->second.end(); ++taskIter)
		{
			(*taskIter)->update();
		}
	}
}

IGameTask* GameTasks::addTask(std::unique_ptr<IGameTask> iTask, int iPriority)
{
	IGameTask* ref = iTask.get();
	_tasks[iPriority].emplace_back(std::move(iTask));
	ref->init();
	return ref;
}

void GameTasks::reset()
{
	for (auto taskGroupIter = _tasks.rbegin(); taskGroupIter != _tasks.rend(); ++taskGroupIter)
	{
		for (auto taskIter = taskGroupIter->second.rbegin(); taskIter != taskGroupIter->second.rend(); ++taskIter)
		{
			(*taskIter)->cleanup();
		}
	}

	_tasks.clear();
}

int GameTasks::getPriority(IGameTask *iTask)
{
	for (auto &taskBucket : _tasks)
	{
		auto found = std::find_if(taskBucket.second.begin(), taskBucket.second.end(), unique_ptr_equals_ptr(iTask));
		if (found != taskBucket.second.end())
			return taskBucket.first;
	}

	return -1;
}

void GameTasks::setPriority(IGameTask *iTask, int iPriority)
{
	std::unique_ptr<IGameTask> task = removeTask(iTask);
	if (task)
	{
		addTask(std::move(task), iPriority);
	}
}

std::unique_ptr<IGameTask> GameTasks::removeTask(IGameTask *iTask)
{
	std::unique_ptr<IGameTask> task;

	for (auto &taskBucket : _tasks) 
	{
		auto found = std::find_if(taskBucket.second.begin(), taskBucket.second.end(), unique_ptr_equals_ptr(iTask));
		if (found != taskBucket.second.end())
		{
			std::unique_ptr<IGameTask> ptr = std::move(*found);
			taskBucket.second.erase(found);
			ptr->cleanup();
			return ptr;
		}
	}

	return nullptr;
}

bool GameEngine::init()
{
	_tasks.init();
	return true;
}

bool GameEngine::run()
{
	_tasks.update();
	return Game<IGameLoopManager>()->exitRequested() == false;
}


bool GameEngine::cleanup()
{
	_tasks.reset();
	
	removeAllComponents();

	return true;

}

IGameTask* GameEngine::addTask(std::unique_ptr<IGameTask> iTask, int iPriority )
{
	return _tasks.addTask(std::move(iTask), iPriority);
}

std::unique_ptr<IGameTask> GameEngine::removeTask(IGameTask *iTask)
{
	return _tasks.removeTask(iTask);
}

void GameEngine::setTaskPriority(IGameTask *iTask, int iPriority)
{
	_tasks.setPriority(iTask, iPriority);
}

int GameEngine::getTaskPriority(IGameTask *iTask)
{
	_tasks.getPriority(iTask);
	return 0;
}

GameEngine::~GameEngine()
{
	GameObjectFactory::reset();
	GameManagerFactory::Instance().reset();
	ComponentFactory::Instance().reset();
}

} // namespace engine
