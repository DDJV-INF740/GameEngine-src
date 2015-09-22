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


//=============================================================================
// CLASS Game
//=============================================================================
class GameEngine 
	: virtual public IGameEngine
	, public ComponentObject<IGameEngine, IGameManager, IGameInterface, GameManagerFactory>
{
public:
	virtual bool init() override;
	virtual bool run() override;
	virtual bool cleanup() override; 

	virtual void addTask(IGameTask *iTask, int iProprity);

	//-------------------------------------------------------------------------
	//
	void setRef(const GameEngineRef &aRef) override
	{
		_ref = aRef;
	}

	//-------------------------------------------------------------------------
	//
	GameEngineRef ref() override
	{
		return _ref.lock();
	}


public:
	std::map<int, std::vector<IGameTask*>> _tasks;
	GameEngineWeakRef _ref;
};

