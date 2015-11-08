#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Game/IGameInterface.h"
#include <memory>

namespace engine
{

//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
class IGameEngine;
typedef std::shared_ptr<IGameEngine> GameEngineRef;
typedef std::weak_ptr<IGameEngine> GameEngineWeakRef;


//=============================================================================
// INTERFACE IGameManager
//=============================================================================
class IGameManager
{
public:
	virtual ~IGameManager() {}

public:
	typedef const char* IdType;
	static IdType NullId;

public:
	virtual IGameInterface::IdType* interfaces() = 0;
	virtual void onAttached(const GameEngineRef &iGameEngine) = 0;
	virtual void onDetached(const GameEngineRef &iGameEngine) = 0;
};
} // namespace engine
