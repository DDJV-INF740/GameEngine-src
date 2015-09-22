#pragma once
//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
#include "Core/Components/IComponentObject.h"
#include "Core/Game/IGameManager.h"
#include "Core/Game/IGameInterface.h"

class IGameInterface;
class IGameTask;


//=============================================================================
// CLASS IGame
//=============================================================================
class IGameEngine;
typedef std::shared_ptr<IGameEngine> GameEngineRef;
typedef std::weak_ptr<IGameEngine> GameEngineWeakRef;

class IGameEngine : virtual public IComponentObject<IGameManager, IGameInterface>
{
public:
	static GameEngineRef Instance();

public:
	virtual bool init()  = 0;
	virtual bool run()  = 0;
	virtual bool cleanup()  = 0;

	virtual void addTask(IGameTask *iTask, int iProprity) = 0;

	virtual GameEngineRef ref() = 0;
	virtual void setRef(const GameEngineRef &aRef) = 0;
};

